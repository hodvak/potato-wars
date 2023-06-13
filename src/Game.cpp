#include "Game.h"
#include "resources_manager.h"
#include "MapObject/Projectile.h"
#include "MapObject/Character.h"
#include "MapObject/Rock.h"
#include "MapObject/BombObject.h"
#include "Weapon/Rifle.h"
#include "Weapon/Creators/RifleWeaponCreator.h"
#include "Weapon/ThrowWeapon.h"
#include "MapObject/Crates/Crate.h"
#include "MapObject/Crates/WeaponCrate.h"
#include "MapObject/Crates/HealthCrate.h"

Game::Game(const std::string &levelName) :
        m_map(levelName), m_camera(m_map.getMask().getSize().x,
                                   m_map.getMask().getSize().y),
        m_weaponCreatorContainer({600, 300}, {100, 100})
{
    m_weaponCreatorContainer.AddWeaponCreator(
            std::make_unique<RifleWeaponCreator>(10, &m_map,
                                                 [&](std::unique_ptr<MovingMapObject> &&m)
                                                 {
                                                     addMovingObject(
                                                             std::move(m));
                                                 },
                                                 m_bombHandler));

    m_weaponCreatorContainer.AddWeaponCreator(
            std::make_unique<RifleWeaponCreator>(3, &m_map,
                                                 [&](std::unique_ptr<MovingMapObject> &&m)
                                                 {
                                                     addMovingObject(
                                                             std::move(m));
                                                 },
                                                 m_bombHandler));

    m_weaponCreatorContainer.AddWeaponCreator(
            std::make_unique<RifleWeaponCreator>(-1, &m_map,
                                                 [&](std::unique_ptr<MovingMapObject> &&m)
                                                 {
                                                     addMovingObject(
                                                             std::move(m));
                                                 },
                                                 m_bombHandler));
    const sf::Image &mask = *resources_manager::getImage(
            "resources/Levels/" + levelName + "/map.bmp"
    );

    for (int x = 0; x < mask.getSize().x; ++x)
    {
        for (int y = 0; y < mask.getSize().y; ++y)
        {
            if (mask.getPixel(x, y) == sf::Color(255, 0, 0))
            {
                auto *character = new Character(
                        sf::Vector2f((float) x, (float) y),
                        &m_map,
                        &m_bombHandler,
                        PlayerColor::RED
                );
                m_movingObjects.emplace_back(character);
                m_characters.push_back(character);
            }
            else if (mask.getPixel(x, y) == sf::Color(0, 255, 0))
            {
                auto *character = new Character(
                        sf::Vector2f((float) x, (float) y),
                        &m_map,
                        &m_bombHandler,
                        PlayerColor::GREEN
                );
                m_movingObjects.emplace_back(character);
                m_characters.push_back(character);

            }
            else if (mask.getPixel(x, y) == sf::Color(0, 0, 255))
            {
                auto *character = new Character(
                        sf::Vector2f((float) x, (float) y),
                        &m_map,
                        &m_bombHandler,
                        PlayerColor::BLUE
                );
                m_movingObjects.emplace_back(character);
                m_characters.push_back(character);
            }
        }
    }

    m_weapon = std::make_unique<ThrowWeapon>(
            *m_characters[1],

            std::make_unique<Rock>(MapVector(0, 0),
                                   MapVector(0, 0),
                                   &m_map,
                                   PlayerColor::BLUE),

            [&](std::unique_ptr<MovingMapObject> &&m)
            {
                addMovingObject(std::move(m));
            }
    );

//    m_weapon = std::make_unique<ThrowWeapon>(
//            *m_characters[1],
//
//            std::make_unique<BombObject>(MapVector(0, 0),
//                                         &m_map,
//                                         &m_bombHandler),
//
//            [&](std::unique_ptr<MovingMapObject> &&m)
//            {
//                addMovingObject(std::move(m));
//            }
//    );


//    m_weapon = std::make_unique<Rifle>(
//            *m_characters[1],
//
//            [&](std::unique_ptr<MovingMapObject> &&m)
//            {
//                addMovingObject(std::move(m));
//            },
//
//            m_map,
//            m_bombHandler
//    );
}

void Game::update(const sf::Time &deltaTime)
{
    updateObjectsInterval(deltaTime, sf::seconds(0.01f));
    // update bombs
    m_bombHandler.update(&m_map, m_movingObjects);

    // remove dead objects
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
    m_camera.setToFollow(objectsToWatch);
    m_camera.update(deltaTime);

    //update weapon
    if (m_weapon && m_weapon->isAlive())
    {
        m_weapon->update(deltaTime);
    }


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
    if (m_weapon && m_weapon->isAlive())
    {
        target.draw(*m_weapon, states);
    }
    else
    {
        target.draw(m_weaponCreatorContainer, states);
    }
}

void Game::updateObjects(sf::Time time)
{
    sf::RectangleShape bounds({(float) m_map.getMask().getSize().x,
                               (float) m_map.getMask().getSize().y});

    for (auto &movingObject: m_movingObjects)
    {
        //update the object`s position and animation
        movingObject->update(time);

        //check if the object is inside the map
        if (!bounds.getGlobalBounds().contains(movingObject->getPosition()))
        {
            movingObject->kill();
        }

    }

    stopMovingObjects();


}

void Game::updateCollision()
{
    for (int i = 0; i < m_movingObjects.size(); ++i)
    {
        for (int j = i + 1; j < m_movingObjects.size(); ++j)
        {
            m_movingObjects[i]->collide(m_movingObjects[j].get());
        }
    }
}

void Game::handleMouseMoved(const MapVector &mousePosition)
{
    if (m_weapon && m_weapon->isAlive())
    {
        m_weapon->handleMouseMoved(mousePosition);
    }
}

void Game::handleMousePressed(const MapVector &mousePosition)
{
//    if (m_weapon && m_weapon->isAlive())
//    {
//        m_weapon->handleMousePressed(mousePosition);
//    }
//    else
//    {
//        WeaponCreator *creator = m_weaponCreatorContainer.GetWeaponCreator(
//                mousePosition);
//        if (creator)
//        {
//            m_weapon = creator->createWeapon(*m_characters[1]);
//        }
//    }
    std::unique_ptr<RifleWeaponCreator> wep = std::make_unique<RifleWeaponCreator>(
            10, &m_map,
            [&](std::unique_ptr<MovingMapObject> &&m)
            {
                addMovingObject(
                        std::move(
                                m));
            },
            m_bombHandler);

    m_movingObjects.emplace_back(
            std::make_unique<HealthCrate>(mousePosition, &m_map));

//    m_movingObjects.emplace_back(std::make_unique<Character>(
//            mousePosition,
//            &m_map,
//            &m_bombHandler,
//            PlayerColor::RED));
//    m_characters.push_back(
//            dynamic_cast<Character *>(m_movingObjects.back().get()));

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
