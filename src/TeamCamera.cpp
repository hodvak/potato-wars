#include <iostream>
#include "TeamCamera.h"
#include "MapVector.h"
#include "resources_manager.h"
TeamCamera::TeamCamera(float width, float height) :
        m_originalViewRect({0, 0, 1080, 720}),
        m_view(m_originalViewRect),
        m_zoomLevel(0)
{

}

void TeamCamera::reset()
{
    m_zoomLevel = 0;

    m_view.reset(m_originalViewRect);
}

void
TeamCamera::update(const sf::Time &deltaTime)
{
    //moving the camera with the mouse
    m_view.getCenter();
    int maxBorder = 100;

    float cameraSpeed = 0.5;
    //moving the camera with the mouse
    if (m_mousePosition.x < 10 )
    {
        m_view.move(-cameraSpeed * deltaTime.asMilliseconds(), 0);
    }
    else if (m_mousePosition.x > resources_manager::SCREEN_WIDTH - 10)
    {
        m_view.move(cameraSpeed * deltaTime.asMilliseconds(), 0);
    }
    if (m_mousePosition.y < 10 )
    {
        m_view.move(0, -cameraSpeed * deltaTime.asMilliseconds());
    }
    else if (m_mousePosition.y > resources_manager::SCREEN_HEIGHT - 10)
    {
        m_view.move(0, cameraSpeed * deltaTime.asMilliseconds());
    }
    //limiting the camera to the map+maxBorder
    if (m_view.getCenter().x - m_view.getSize().x/2  <  -maxBorder)
    {
        m_view.setCenter(-maxBorder + m_view.getSize().x/2, m_view.getCenter().y);
    }
    else if (m_view.getCenter().x + m_view.getSize().x/2>  resources_manager::SCREEN_WIDTH + maxBorder)
    {
        m_view.setCenter(resources_manager::SCREEN_WIDTH + maxBorder - m_view.getSize().x/2, m_view.getCenter().y);
    }
    if (m_view.getCenter().y - m_view.getSize().y/2  <  -maxBorder)
    {
        m_view.setCenter(m_view.getCenter().x, -maxBorder + m_view.getSize().y/2);
    }
    else if (m_view.getCenter().y + m_view.getSize().y/2>  resources_manager::SCREEN_HEIGHT + maxBorder)
    {
        m_view.setCenter(m_view.getCenter().x, resources_manager::SCREEN_HEIGHT + maxBorder - m_view.getSize().y/2);
    }


}

void TeamCamera::handleScroll(int delta)
{
    //zooming in and out with the mouse wheel
    float zoomSpeed = -0.5;
    int maxZoom = 1;
    int minZoom = -5.5;
    m_zoomLevel += delta * zoomSpeed;
    if (m_zoomLevel > maxZoom)
    {
        m_zoomLevel = maxZoom;
    }
    else if (m_zoomLevel < minZoom)
    {
        m_zoomLevel = minZoom;
    }
    m_view.setSize(m_originalViewRect.width * std::pow(1.1, m_zoomLevel),
                   m_originalViewRect.height * std::pow(1.1, m_zoomLevel));



}

const sf::View &TeamCamera::getView() const
{
    return m_view;
}

void TeamCamera::handleMouseMoved(const sf::Vector2<int> &mousePosition)
{
    m_mousePosition = mousePosition;
}
