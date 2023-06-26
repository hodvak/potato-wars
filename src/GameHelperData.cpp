#include "GameHelperData.h"
#include "MapObject/Rock.h"

GameHelperData::GameHelperData(GameMap &map,
                               BombHandler &bombHandler,
                               sf::RenderWindow *window,
                               sf::Time deltaTime) :
        m_map(map),
        m_bombHandler(bombHandler),
        m_window(window),
        m_deltaTime(deltaTime)
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

void GameHelperData::addMapObject(std::unique_ptr<MovingMapObject> &&mapObject)
{
    m_addMapObjectFunc(std::move(mapObject));
}

void GameHelperData::setAddObjectFunc(
        const std::function<void(std::unique_ptr<MovingMapObject> &&)> &func)
{
    m_addMapObjectFunc = func;
}


