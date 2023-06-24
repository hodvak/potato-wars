#include "GameHelperData.h"

GameHelperData::GameHelperData(GameMap &m_map,
                               BombHandler &m_bombHandler,
                               sf::RenderWindow *m_window,
                               sf::Time m_deltaTime):
        m_map(m_map),
        m_bombHandler(m_bombHandler),
        m_window(m_window),
        m_deltaTime(m_deltaTime)
{

}

const sf::Time &GameHelperData::getDeltaTime() const
{
    return m_deltaTime;
}

sf::Vector2i GameHelperData::getMousePositionInWindow() const
{
    return sf::Mouse::getPosition(*m_window);
}

sf::Vector2f GameHelperData::getMousePositionInMap() const
{
    return m_window->mapPixelToCoords(getMousePositionInWindow());
}

sf::Vector2u GameHelperData::getWindowSize() const
{
    return m_window->getSize();
}

GameMap &GameHelperData::getMap() const
{
    return m_map;
}

BombHandler &GameHelperData::getBombHandler() const
{
    return m_bombHandler;
}

void GameHelperData::setDeltaTime(const sf::Time &deltaTime)
{
    m_deltaTime = deltaTime;
}

void GameHelperData::setWindow(const sf::RenderWindow &window)
{
    m_window = &window;
}


