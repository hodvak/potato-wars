
#include "camera.h"

void Camera::setToFolow(MovingMapObject *object)
{
    m_object = object;
    m_view.setSize(1080,720);
    m_view.zoom(0.5f);
}

void Camera::update(sf::RenderWindow *window)
{
    if(m_object == nullptr)
    {
        m_view.setCenter(window->getSize().x / 2, window->getSize().y / 2);


    }
    else
    {
        m_view.setCenter(m_object->get_position().x, m_object->get_position().y);
        if (!m_object->is_alive()||m_object->is_rest())
        {
            m_object = nullptr;
            m_view.zoom(2.0f);
        }


    }
    window->setView(m_view);
}

Camera::Camera():
    m_view(sf::FloatRect(0, 0, 1080, 720))
{

}
