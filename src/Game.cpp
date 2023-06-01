#include "Game.h"
#include "resources_manager.h"
#include "MapObject/Projectile.h"

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
                m_movingObjects.emplace_back(
                        std::make_unique<Ball>(
                                sf::Vector2f((float) x, (float) y),
                                &m_map,
                                &m_bombHandler,
                                PlayerColor::RED)
                );
            }
            else if (mask.getPixel(x, y) == sf::Color(0, 255, 0))
            {
                m_movingObjects.emplace_back(
                        std::make_unique<Ball>(
                                sf::Vector2f((float) x, (float) y),
                                &m_map,
                                &m_bombHandler,
                                PlayerColor::GREEN)
                );
            }
            else if (mask.getPixel(x, y) == sf::Color(0, 0, 255))
            {
                m_movingObjects.emplace_back(
                        std::make_unique<Ball>(
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

    // update objects
    for (auto &movingObject: m_movingObjects)
    {
        movingObject->update(deltaTime.asSeconds());
    }

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

    // double dispatch
    for (int i = 0; i < m_movingObjects.size(); ++i)
    {
        for (int j = i + 1; j < m_movingObjects.size(); ++j)
        {
            // calculate distance between objects
            float distance_square =
                    std::pow(m_movingObjects[i]->getPosition().x -
                             m_movingObjects[j]->getPosition().x,
                             2) +
                    std::pow(m_movingObjects[i]->getPosition().y -
                             m_movingObjects[j]->getPosition().y,
                             2);
            if (distance_square > std::pow(m_movingObjects[i]->getRadius() +
                                           m_movingObjects[j]->getRadius(),
                                           2))
            {
                continue;
            }
            if (!m_movingObjects[i]->collide(m_movingObjects[j].get()))
            {
                m_movingObjects[j]->collide(m_movingObjects[i].get());
            }
        }
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
                                MapVector(300, 300),
                                &m_map,
                                &m_bombHandler)
                );
            }
            else if (event.mouseButton.button == sf::Mouse::Right)
            {
                m_movingObjects.emplace_back(
                        std::make_unique<Ball>(
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
    target.draw(m_map, states);
    for (const auto &movingObject: m_movingObjects)
    {
        target.draw(*movingObject, states);
    }
}