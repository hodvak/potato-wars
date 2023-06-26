#include <iostream>
#include "TeamCamera.h"
#include "MapVector.h"
#include "resources_manager.h"

TeamCamera::TeamCamera(sf::FloatRect mapRect,
                       sf::Vector2f originalViewSize,
                       GameHelperData &gameHelperData) :
        m_mapRect(mapRect),
        m_originalViewSize(originalViewSize),
        m_gameHelperData(gameHelperData),
        m_zoomLevel(0),
        m_position(mapRect.left + mapRect.width / 2.0f,
                   mapRect.top + mapRect.height / 2.0f),
        m_viewRect(m_position.x - originalViewSize.x / 2.0f,
                   m_position.y - originalViewSize.y / 2.0f,
                   originalViewSize.x,
                   originalViewSize.y)
                   
{

}

void TeamCamera::reset()
{
    m_zoomLevel = 0;
    m_position = {m_mapRect.left + m_mapRect.width / 2.0f,
                  m_mapRect.top + m_mapRect.height / 2.0f};
}

void
TeamCamera::update(const sf::Time &deltaTime)
{
    sf::Vector2i mousePosition = m_gameHelperData.getMousePositionInWindow();
    if(mousePosition.x < 0 ||
            mousePosition.y < 0 ||
            mousePosition.x > m_gameHelperData.getWindowSize().x ||
            mousePosition.y > m_gameHelperData.getWindowSize().y)
    {
        return;
    }
    
    if (mousePosition.x <
        m_gameHelperData.getWindowSize().x * 0.05f)
    {
        std::cout << "left" << std::endl;
        m_position.x -= 1000 * deltaTime.asSeconds();
        fixBorders();
        std::cout << m_viewRect.left + m_viewRect.width / 2.0f << " " << m_viewRect.top + m_viewRect.height / 2.0f << std::endl;


    }
    else if (mousePosition.x >
             m_gameHelperData.getWindowSize().x * 0.95f)
    {
        m_position.x += 1000 * deltaTime.asSeconds();
    }
    if (mousePosition.y <
        m_gameHelperData.getWindowSize().y * 0.05f)
    {
        m_position.y -= 1000 * deltaTime.asSeconds();
    }
    else if (mousePosition.y >
             m_gameHelperData.getWindowSize().y * 0.95f)
    {
        m_position.y += 1000 * deltaTime.asSeconds();
    }
    
    m_viewRect.left = m_position.x - m_viewRect.width / 2.0f;
    m_viewRect.top = m_position.y - m_viewRect.height / 2.0f;
    fixBorders();


}

void TeamCamera::handleScroll(float delta)
{
    m_zoomLevel += delta * ZOOM_SPEED;
    if (m_zoomLevel > MAX_ZOOM)
    {
        m_zoomLevel = MAX_ZOOM;
    }
    else if (m_zoomLevel < MIN_ZOOM)
    {
        m_zoomLevel = MIN_ZOOM;
    }
    m_viewRect.width = m_originalViewSize.x * std::pow(0.9f, m_zoomLevel);
    m_viewRect.height = m_originalViewSize.y * std::pow(0.9f, m_zoomLevel);
    m_viewRect.left = m_position.x - m_viewRect.width / 2.0f;
    m_viewRect.top = m_position.y - m_viewRect.height / 2.0f;
    fixBorders();

}

sf::View TeamCamera::getView() const
{
    sf::View view;
    view.setCenter(m_viewRect.left + m_viewRect.width / 2.0f,
                   m_viewRect.top + m_viewRect.height / 2.0f);
    std::cout << m_viewRect.left + m_viewRect.width / 2.0f << " " << m_viewRect.top + m_viewRect.height / 2.0f << std::endl;
    view.setSize(m_viewRect.width, m_viewRect.height);
    return view;
}

void TeamCamera::handleMouseMoved(const sf::Vector2<int> &mousePosition)
{
//    m_mousePosition = mousePosition;
}

void TeamCamera::fixBorders()
{
    if (m_viewRect.left < m_mapRect.left)
    {
        m_viewRect.left = m_mapRect.left;
    }
    else if (m_viewRect.left + m_viewRect.width >
             m_mapRect.left + m_mapRect.width)
    {
        m_viewRect.left = m_mapRect.left + m_mapRect.width - m_viewRect.width;
    }

    if (m_viewRect.top < m_mapRect.top)
    {
        m_viewRect.top = m_mapRect.top;
    }
    else if (m_viewRect.top + m_viewRect.height >
             m_mapRect.top + m_mapRect.height)
    {
        m_viewRect.top = m_mapRect.top + m_mapRect.height - m_viewRect.height;
    }
}
