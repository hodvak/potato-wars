#include "Game.h"
#include "resources_manager.h"
#include "MapObject/Projectile.h"
#include "Physics.h"

Game::Game(const std::string &levelName) :
        m_map(levelName), m_camera(m_map.getMask().getSize().x,
                                   m_map.getMask().getSize().y)
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
                m_movingObjects.emplace_back(
                        std::make_unique<Character>(
                                sf::Vector2f((float) x, (float) y),
                                &m_map,
                                &m_bombHandler,
                                PlayerColor::RED)
                );
            } else if (mask.getPixel(x, y) == sf::Color(0, 255, 0))
            {
                m_movingObjects.emplace_back(
                        std::make_unique<Character>(
                                sf::Vector2f((float) x, (float) y),
                                &m_map,
                                &m_bombHandler,
                                PlayerColor::GREEN)
                );
            } else if (mask.getPixel(x, y) == sf::Color(0, 0, 255))
            {
                m_movingObjects.emplace_back(
                        std::make_unique<Character>(
                                sf::Vector2f((float) x, (float) y),
                                &m_map,
                                &m_bombHandler,
                                PlayerColor::BLUE)
                );
            }
        }
    }
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
    std::vector<MovingMapObject *> objectsToWatch;
    for (const auto &object: m_movingObjects)
    {
        if (!object->isRest()) objectsToWatch.push_back(object.get());
    }
    m_camera.setToFollow(objectsToWatch);
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
        } else
        {
            updateObjects(interval);
        }
        updateCollision();
        time += interval;
    }
}

void Game::handleEvent(const sf::Event &event)
{
    switch (event.type)
    {
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                m_movingObjects.emplace_back(
                        std::make_unique<Projectile>(
                                50,
                                sf::Vector2f((float) event.mouseButton.x,
                                             (float) event.mouseButton.y),
                                3,
                                0.3,
                                MapVector(600, 300),
                                &m_map,
                                &m_bombHandler)
                );
            } else if (event.mouseButton.button == sf::Mouse::Right)
            {
                m_movingObjects.emplace_back(
                        std::make_unique<Character>(
                                sf::Vector2f((float) event.mouseButton.x,
                                             (float) event.mouseButton.y),
                                &m_map,
                                &m_bombHandler,
                                PlayerColor::RED)
                );
            }
            break;
        default:
            break;
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
