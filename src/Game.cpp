#include "Game.h"
#include "resources_manager.h"
#include "MapObject/Projectile.h"
#include "MapObject/Character.h"
#include "MapObject/Rock.h"

#include "Weapon/Creators/RifleWeaponCreator.h"
#include "MapObject/Crates/WeaponCrate.h"
#include "Weapon/Creators/StoneThrowCreator.h"
#include "Weapon/Creators/JumpCreator.h"
#include "Weapon/Creators/BombThrowCreator.h"
#include "MapObject/Crates/HealthCrate.h"
#include "Weapon/Creators/MinigunWeaponCreator.h"


#include <functional>
#include <format>

Game::Game(int levelNumber) :
        m_map(levelNumber),
        m_helperData(m_map, m_bombHandler),
        m_soundPlayer(),

        m_camera((float) m_map.getMask().getSize().x,
                 (float) m_map.getMask().getSize().y),

        m_teamTurnIndex(0),
        m_teams{Team(PlayerColor::YELLOW, m_helperData),
                Team(PlayerColor::GREEN, m_helperData),
                Team(PlayerColor::RED, m_helperData),
                Team(PlayerColor::BLUE, m_helperData)},

        m_crateDropper((int) m_map.getMask().getSize().x,
                       [this](std::unique_ptr<MovingMapObject> &&object)
                       {
                           addMovingObject(
                                   std::move(object));
                       },
                       m_map,
                       m_bombHandler),
        m_teamCamera((float) m_map.getMask().getSize().x,
                     (float) m_map.getMask().getSize().y),
        m_allStopped(false)
{
    const sf::Image &mask = *resources_manager::getImage(
            std::vformat(resources_manager::PATH_LEVELS,
                         std::make_format_args(levelNumber)));

    for (int x = 0; x < mask.getSize().x; ++x)
    {
        for (int y = 0; y < mask.getSize().y; ++y)
        {
            for (int i = 0; i < PlayerColor::SIZE; ++i)
            {
                if (mask.getPixel(x, y) == getColor((PlayerColor) i))
                {
                    addCharacter(PlayerColor(i), MapVector((float) x,
                                                           (float) y));
                }
            }
        }
    }
    while (m_teams[m_teamTurnIndex].isDead())
    {
        m_teamTurnIndex = (m_teamTurnIndex + 1) % PlayerColor::SIZE;
    }
}

void Game::update(const sf::Time &deltaTime)
{
    //update objects
    updateObjectsInterval(deltaTime, sf::seconds(0.001f));
    stopMovingObjects();
    m_map.update(deltaTime);
    //update team
    if (m_teams[m_teamTurnIndex].update(deltaTime, m_allStopped))
    {
        m_teamTurnIndex = (m_teamTurnIndex + 1) % PlayerColor::SIZE;


        while (m_teams[m_teamTurnIndex].isDead())
        {

            m_teamTurnIndex = (m_teamTurnIndex + 1) % PlayerColor::SIZE;
        }
        for (int i = 0; i < 5; ++i)
        {
            m_crateDropper.dropCrate();
        }

    }

    // update bombs
    m_bombHandler.update(&m_map, m_movingObjects);
    m_soundPlayer.play();



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
    m_teamCamera.update(deltaTime);

    m_teamCamera.handleMouseMoved(m_helperData.getMousePositionInWindow());
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
    target.setView(m_teamCamera.getView());
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


void Game::handleMousePressed()
{


    //m_teamCamera.reset();
    // TODO: understand the non virtual destructor warning


//    m_movingObjects.emplace_back(std::move(crate));
    m_soundPlayer.addSound("resources/Sounds/eatGift.wav");
    m_teams[m_teamTurnIndex].onMouseClick();
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
    m_allStopped = toStop;
    if (toStop)
    {
        for (auto &object: m_movingObjects)
        {
            object->stop();
        }

    }
    int x = 3;
    std::unique_ptr<Crate> healthCrate = std::make_unique<HealthCrate>(
            MapVector(0, 0), m_map, m_bombHandler);
    std::unique_ptr<Crate> crate = std::make_unique<HealthCrate>(
            MapVector{float(x), 0}, m_map, m_bombHandler);
    std::vector<std::unique_ptr<Crate>> crates;
    crates.emplace_back(std::make_unique<HealthCrate>(MapVector(0, 0), m_map,
                                                      m_bombHandler));
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

    character->addWeaponCreator(std::make_unique<MinigunWeaponCreator>(
            1,
            [&](std::unique_ptr<MovingMapObject> &&object)
            {
                addMovingObject(std::move(object));
            },
            m_map,
            m_bombHandler
    ));

    character->addWeaponCreator(std::make_unique<JumpCreator>(
            -1,
            [&](std::unique_ptr<MovingMapObject> &&object)
            {
                addMovingObject(
                        std::move(
                                object));
            }

    ));
    character->addWeaponCreator(std::make_unique<BombThrowCreator>(
            1,
            [&](std::unique_ptr<MovingMapObject> &&object)
            {
                addMovingObject(
                        std::move(
                                object));
            },
            m_map,
            m_bombHandler

    ));

    m_movingObjects.emplace_back(character);
    m_teams[color].addCharacter(character);
}

void Game::handleScroll(int delta)
{
    m_teamCamera.handleScroll(delta);
}

void Game::setWindow(const sf::RenderWindow &window)
{
    m_helperData.setWindow(window);
    m_map.setTarget(&window);
}
