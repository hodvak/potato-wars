#include "Game.h"
#include "resources_manager.h"
#include "MapObject/Projectile.h"
#include "MapObject/Character.h"
#include "MapObject/Rock.h"
#include "MapObject/BombObject.h"
#include "Weapon/Creators/RifleWeaponCreator.h"
#include "MapObject/Crates/WeaponCrate.h"
#include "Weapon/Creators/StoneThrowCreator.h"
#include "Weapon/Creators/JumpCreator.h"

#include <functional>

Game::Game(const std::string &levelName) :
        m_map(levelName), m_camera(m_map.getMask().getSize().x,
                                   m_map.getMask().getSize().y),
        m_teamTurnIndex(2),
        m_teams{Team(PlayerColor::YELLOW),
                Team(PlayerColor::GREEN),
                Team(PlayerColor::RED),
                Team(PlayerColor::BLUE)}
{
    const sf::Image &mask = *resources_manager::getImage(
            "resources/Levels/" + levelName + "/map.bmp"
    );

    for (int x = 0; x < mask.getSize().x; ++x)
    {
        for (int y = 0; y < mask.getSize().y; ++y)
        {
            for (int i = 0; i < PlayerColor::SIZE; ++i)
            {
                if (mask.getPixel(x, y) == getColor((PlayerColor) i))
                {
                    addCharacter(PlayerColor(i), MapVector(x, y));
                }
            }
        }
    }
}

void Game::update(const sf::Time &deltaTime)
{
    //update objects
    updateObjectsInterval(deltaTime, sf::seconds(0.001f));
    stopMovingObjects();

    //update team
    if (m_teams[m_teamTurnIndex].update(deltaTime))
    {
        m_teamTurnIndex = (m_teamTurnIndex + 1) % PlayerColor::SIZE;
        std::cout << "team " << m_teamTurnIndex << " is done with their turn"
                  << std::endl;
        while (m_teams[m_teamTurnIndex].isDead())
        {
            std::cout << "team " << m_teamTurnIndex << " is dead" << std::endl;
            m_teamTurnIndex = (m_teamTurnIndex + 1) % PlayerColor::SIZE;
        }
    }

    // update bombs
    m_bombHandler.update(&m_map, m_movingObjects);
    m_teams[m_teamTurnIndex].update(deltaTime);

    // remove dead objects
    // from teams
    for (auto &team: m_teams)
    {
        team.removeDeadCharacters();
    }

    // from moving objects (must be last because the unique_ptr)
    m_movingObjects.erase(
            std::remove_if(m_movingObjects.begin(), m_movingObjects.end(),
                           [](const std::unique_ptr<MovingMapObject> &object)
                           {
                               return !object->isAlive();
                           }),
            m_movingObjects.end()
    );

    //update camera
    std::vector<MovingMapObject *> objectsToWatch;
    for (const auto &object: m_movingObjects)
    {
        if (!object->isRest())
        { objectsToWatch.push_back(object.get()); }
    }
    m_camera.setToFollow(std::move(objectsToWatch));
    m_camera.update(deltaTime);
}

void
Game::updateObjectsInterval(const sf::Time &deltaTime, const sf::Time &interval)
{
    sf::Time time = sf::Time::Zero;
    while (time < deltaTime)
    {
        if (time + interval > deltaTime)
        {
            updateObjects(deltaTime - time);
        }
        else
        {
            updateObjects(interval);
        }
        updateCollision();
        time += interval;
    }
}


void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.setView(m_camera.getView());
    target.draw(m_map, states);
    for (const auto &movingObject: m_movingObjects)
    {
        target.draw(*movingObject, states);
    }
    target.draw(m_teams[m_teamTurnIndex], states);
}

void Game::updateObjects(const sf::Time &time)
{
    sf::RectangleShape bounds({(float) m_map.getMask().getSize().x,
                               (float) m_map.getMask().getSize().y});

    for (auto &movingObject: m_movingObjects)
    {
        //update the object's position and animation
        movingObject->update(time);

        //check if the object is inside the map
        if (!bounds.getGlobalBounds().contains(movingObject->getPosition()))
        {
            movingObject->kill();
        }

    }
}

void Game::updateCollision()
{
    for (int i = 0; i < m_movingObjects.size(); ++i)
    {
        for (int j = i + 1; j < m_movingObjects.size(); ++j)
        {
            m_movingObjects[i]->collide(*m_movingObjects[j]);
        }
    }
}

void Game::handleMouseMoved(const MapVector &mousePosition)
{
    m_teams[m_teamTurnIndex].onMouseMove(mousePosition);
}

void Game::handleMousePressed(const MapVector &mousePosition)
{
    std::unique_ptr<RifleWeaponCreator> rifleCreator = std::make_unique<RifleWeaponCreator>(
            1,
            [&](std::unique_ptr<MovingMapObject> &&object)
            {
                addMovingObject(std::move(object));
            },
            m_map,
            m_bombHandler
    );
    std::unique_ptr<StoneThrowCreator> rockCreator = std::make_unique<StoneThrowCreator>(
            1,
            [&](std::unique_ptr<MovingMapObject> &&object)
            {
                addMovingObject(std::move(object));
            },
            m_map,
            m_bombHandler
    );
    
    // todo: understand the non virtual destructor warning
    
    std::unique_ptr<WeaponCrate> crate = std::make_unique<WeaponCrate>(
            mousePosition,
            std::move(rifleCreator),
            m_map,
            m_bombHandler
    );

//    m_movingObjects.emplace_back(std::move(crate));
    m_teams[m_teamTurnIndex].onMouseClick(mousePosition);
}

void Game::addMovingObject(std::unique_ptr<MovingMapObject> &&object)
{
    m_movingObjects.emplace_back(std::move(object));
}

void Game::stopMovingObjects()
{
    bool toStop = std::all_of(m_movingObjects.begin(), m_movingObjects.end(),
                              [](const std::unique_ptr<MovingMapObject> &object)
                              {
                                  return object->isRest() ||
                                         object->getMovementTime().asSeconds() >
                                         2;
                              });
    if (toStop)
    {
        for (auto &object: m_movingObjects)
        {
            object->stop();
        }
    }
}

void Game::addCharacter(const PlayerColor &color, const MapVector &position)
{
    auto *character = new Character(
            position,
            m_map,
            m_bombHandler,
            color
    );
    
    
    character->addWeaponCreator(std::make_unique<StoneThrowCreator>(
            -1,
            [&](std::unique_ptr<MovingMapObject> &&object)
            {
                addMovingObject(std::move(object));
            },
            m_map,
            m_bombHandler
    ));
    
    character->addWeaponCreator(std::make_unique<RifleWeaponCreator>(
            1,
            [&](std::unique_ptr<MovingMapObject> &&object)
            {
                addMovingObject(std::move(object));
            },
            m_map,
            m_bombHandler
    ));

    character->addWeaponCreator(std::make_unique<JumpCreator>(-1,
                                                              [&](std::unique_ptr<MovingMapObject> &&object)
                                                              {
                                                                  addMovingObject(std::move(object));
                                                              }

    ));

    m_movingObjects.emplace_back(character);
    m_teams[color].addCharacter(character);
}
