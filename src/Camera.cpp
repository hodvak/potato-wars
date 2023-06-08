

#include "Camera.h"
#include <cmath>

#include <utility>

Camera::Camera(float width, float hight) : m_view({0, 0, width, hight}),
                                           screenSize(width, hight)
{

}

void Camera::setToFollow(std::vector<MovingMapObject *> objectToWatch)
{
    m_objectsToWatch = std::move(objectToWatch);
}

const sf::View &Camera::getView() const
{
    return m_view;
}

void Camera::update(sf::Time deltaTime)
{
    sf::Vector2f center(screenSize.x / 2, screenSize.y / 2);
    sf::Vector2f viewSize = screenSize;

    if (!m_objectsToWatch.empty())
    {
        float minX = 200000;
        float minY = 200000;
        float maxX = -200000;
        float maxY = -200000;

        for (auto &object: m_objectsToWatch)
        {
            minX = std::min(minX,
                            object->getPosition().x - 3 * object->getRadius());
            minY = std::min(minY,
                            object->getPosition().y - 3 * object->getRadius());
            maxX = std::max(maxX,
                            object->getPosition().x + 3 * object->getRadius());
            maxY = std::max(maxY,
                            object->getPosition().y + 3 * object->getRadius());
        }

        float ratioWH = screenSize.x / screenSize.y;
        center = {minX + (maxX - minX) / 2,
                  minY + (maxY - minY) / 2};
        viewSize = {std::max(maxX - minX, 600.0f),
                    std::max(maxY - minY, 600.0f)};
        if (viewSize.x / viewSize.y > ratioWH)
        {
            viewSize.y = viewSize.x / ratioWH;
        } else
        {
            viewSize.x = viewSize.y * ratioWH;
        }
    }
    sf::View prevView = m_view;

    // zoom smoothly
    float maxSizeRatio = pow(1.3, deltaTime.asSeconds());
    float ratio = std::max(viewSize.x, prevView.getSize().x) /
                  std::min(viewSize.x, prevView.getSize().x);

    if (ratio > maxSizeRatio)
    {
        if (viewSize.x > prevView.getSize().x)
        {
            viewSize = prevView.getSize() * maxSizeRatio;
        } else
        {
            viewSize = prevView.getSize() / maxSizeRatio;
        }
    }

    // move center smoothly
    float maxMoveDiff = 100 * deltaTime.asSeconds();
    sf::Vector2i dir = {center.x > prevView.getCenter().x ? 1 : -1,
                        center.y > prevView.getCenter().y ? 1 : -1};

    sf::Vector2f moveDiff = {center.x - prevView.getCenter().x,
                             center.y - prevView.getCenter().y};
    if (std::abs(moveDiff.x) > maxMoveDiff)
    {
        moveDiff.x = maxMoveDiff * dir.x;
    }
    if (std::abs(moveDiff.y) > maxMoveDiff)
    {
        moveDiff.y = maxMoveDiff * dir.y;
    }

    center = prevView.getCenter() + moveDiff;





    m_view.setSize(viewSize);
    m_view.setCenter(center);
}

