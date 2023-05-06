
#include "Camera.h"

void Camera::setToFollow(MovingMapObject *object)
{
    m_object = object;
    m_view.setSize(GameMap::WIDTH * 0.5f, GameMap::HEIGHT * 0.5f);
}

void Camera::update(sf::RenderWindow *window)
{
    if (m_object == nullptr)
    {
        m_view.setCenter((float) window->getSize().x / 2,
                         (float) window->getSize().y / 2);
    }
    else
    {
        m_view.setCenter(m_object->getPosition().x,
                         m_object->getPosition().y);
        if (!m_object->isAlive() || m_object->isRest())
        {
            m_object = nullptr;
            m_view.setSize(GameMap::WIDTH, GameMap::HEIGHT);
        }


    }
    window->setView(m_view);
}

Camera::Camera() :
        m_view(sf::FloatRect(0, 0, GameMap::WIDTH, GameMap::HEIGHT))
{

}
