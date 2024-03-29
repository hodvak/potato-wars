#include "Game.h"
#include "resources_manager.h"
#include "MapObject/Projectile.h"
#include "MapObject/Character.h"
#include "MapObject/Rock.h"

#include "MapObject/Crates/WeaponCrate.h"
#include "Weapon/Creators/StoneThrowCreator.h"
#include "Weapon/Creators/BombThrowCreator.h"
#include "MapObject/Crates/HealthCrate.h"
#include "MapObject/Missile.h"
#include "Weapon/Creators/BazookaCreator.h"
#include "Weapon/Creators/TargetBazookaCreator.h"

#include "Weapon/Creators/MinigunWeaponCreator.h"
#include "MapObject/Fragments.h"

#include <functional>
#include <format>

Game::Game(const Level &level) :
        m_map(level),
        m_soundPlayer(false, 100),
        m_bombHandler(),
        m_helperData(m_map, m_bombHandler, m_soundPlayer),

        m_camera((float) m_map.getMask().getSize().x,
                 (float) m_map.getMask().getSize().y),

        m_teamTurnIndex(0),
        m_teams{Team(PlayerColor::YELLOW, m_helperData),
                Team(PlayerColor::GREEN, m_helperData),
                Team(PlayerColor::RED, m_helperData),
                Team(PlayerColor::BLUE, m_helperData)},

        m_crateDropper((int) m_map.getMask().getSize().x,
                       m_helperData),

        m_teamCamera(m_helperData),
        m_allStopped(false)
{
    m_helperData.setAddObjectFunc([this](auto object)
                                  {
                                      addMovingObject(std::move(object));
                                  });
    m_bombHandler.setAddFragments([this](auto pos, auto dir)
                                  {
                                      addFragments(pos, dir);
                                  });
    const sf::Image mask = resources_manager::get<sf::Image>(
            std::vformat(resources_manager::PATH_LEVELS,
                         std::make_format_args(level.levelNumber)));

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

PlayerColor Game::update(const sf::Time &deltaTime)
{
    //update objects
    m_teamCamera.update(deltaTime);

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

        m_crateDropper.dropCrate();


    }

    // update bombs
    m_bombHandler.update(&m_map, m_movingObjects);
    m_soundPlayer.play();



    // remove dead objects
    // from teams
    for (auto &team: m_teams)
    {
        if (team.removeDeadCharacters())
        {
            m_teamTurnIndex = (m_teamTurnIndex + 1) % PlayerColor::SIZE;

            while (m_teams[m_teamTurnIndex].isDead())
            {

                m_teamTurnIndex = (m_teamTurnIndex + 1) % PlayerColor::SIZE;
            }
        }
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

    m_teamCamera.handleMouseMoved(
            {(int) m_helperData.getMousePositionInWindow().x,
             (int) m_helperData.getMousePositionInWindow().y});

    return winingTeam();
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
    sf::View view;
    if (!m_teams[m_teamTurnIndex].takeFocus())
    {
        view = m_teamCamera.getView();
    }
    else
    {
        view = m_camera.getView();
    }
    target.setView(view);
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
    m_teams[m_teamTurnIndex].onMouseClick();
}

void Game::addMovingObject(std::unique_ptr<MovingMapObject> &&object)
{
    m_movingObjects.push_back(std::move(object));
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

}

void Game::addCharacter(const PlayerColor &color, const MapVector &position)
{
    auto *character = new Character(
            position,
            m_helperData,
            color
    );


    character->addWeaponCreator(std::make_unique<StoneThrowCreator>(
            -1,
            m_helperData
    ));


    character->addWeaponCreator(std::make_unique<BombThrowCreator>(
            1,
            m_helperData
    ));


    m_teams[color].addCharacter(character);
    m_movingObjects.emplace_back(character);
}

void Game::handleScroll(float delta)
{
    m_teamCamera.handleScroll(delta);
}

void Game::setWindow(const sf::RenderWindow &window)
{
    m_helperData.setWindow(window);
    m_map.setTarget(&window);
}

PlayerColor Game::winingTeam() const
{
    PlayerColor winingTeam = PlayerColor::SIZE;
    int amount = 0;
    for (auto &team: m_teams)
    {
        if (!team.isDead())
        {
            winingTeam = team.getColor();
            amount++;
        }
    }
    if (amount > 1)
    {
        return PlayerColor::SIZE;
    }
    return winingTeam;
}

void Game::addFragments(MapVector pos, MapVector velocity)
{
    m_movingObjects.emplace_back(new Fragments(pos, m_helperData, velocity));
}


void Game::m_ChangeVolume(float volume)
{
    m_soundPlayer.setVolume(volume);
}

void Game::m_setMute(bool mute)
{
    m_soundPlayer.setMute(mute);
}
