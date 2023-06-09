#include "Game.h"
#include "resources_manager.h"
#include "MapObject/Projectile.h"
#include "MapObject/Character.h"
#include "MapObject/Rock.h"
#include "Weapon/ThrowWeapon.h"
#include "Physics.h"

Game::Game(const std::string &levelName) :
        m_map(levelName)
{
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
    m_weapon = std::make_unique<ThrowWeapon>(*m_characters[0],
                                             *(new Rock(sf::Vector2f(0, 0),
                                                         sf::Vector2f (0, 0),
                                                             &m_map,
                                                             PlayerColor::RED)),
                                             [&](MovingMapObject &m)
                                             {
                                                 m_movingObjects.emplace_back(
                                                         &m);
                                             });
}

void Game::update(const sf::Time &deltaTime)
{
    updateObjectsInterval(deltaTime, sf::seconds(0.001f));
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

    if (m_weapon->isAlive())
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
    target.draw(m_map, states);
    for (const auto &movingObject: m_movingObjects)
    {
        target.draw(*movingObject, states);
    }
    if (m_weapon->isAlive())
    {
        target.draw(*m_weapon, states);
    }
}

void Game::updateObjects(sf::Time time)
{
    for (auto &movingObject: m_movingObjects)
    {
        movingObject->update(time);
    }

}

void Game::updateCollision()
{
    for (int i = 0; i < m_movingObjects.size(); ++i)
    {
        for (int j = i + 1; j < m_movingObjects.size(); ++j)
        {
            if (m_movingObjects[i]->intersect(*m_movingObjects[j]))
            {
                if (!m_movingObjects[i]->collide(m_movingObjects[j].get()))
                {
                    m_movingObjects[j]->collide(m_movingObjects[i].get());
                }
            }
        }
    }
}

void Game::handleMouseMoved(const MapVector &mousePosition)
{
    if (m_weapon->isAlive())
    {
        m_weapon->handleMouseMoved(mousePosition);
    }
}

void Game::handleMousePressed(const MapVector &mousePosition)
{
    if (m_weapon->isAlive())
    {
        m_weapon->handleMousePressed(mousePosition);
    }
}
