
#include "camera.h"

void Camera::set_to_follow(MovingMapObject *object)
{
    m_object = object;
    m_view.setSize(Map::WIDTH * 0.5f, Map::HEIGHT * 0.5f);
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
        m_view.setCenter(m_object->get_position().x,
                         m_object->get_position().y);
        if (!m_object->is_alive() || m_object->is_rest())
        {
            m_object = nullptr;
            m_view.setSize(Map::WIDTH, Map::HEIGHT);
        }


    }
    window->setView(m_view);
}

Camera::Camera() :
        m_view(sf::FloatRect(0, 0, Map::WIDTH, Map::HEIGHT))
{

}
