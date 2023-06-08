

#include "Camera.h"

#include <utility>

Camera::Camera(float width, float hight):m_view({0, 0, width, hight})
{

}

void Camera::setToFollow(std::vector<MovingMapObject *> objectToWatch)
{
    m_objectsToWatch = std::move(objectToWatch);
}

