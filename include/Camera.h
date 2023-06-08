#pragma once

#include <SFML/Graphics.hpp>
#include "MapObject/MovingMapObject.h"

/**
 * a class that handle camera movement, focus and zoom
 */
class Camera
{
public:
    /**
     * regular constructor
     */
    Camera(float width,float hight);

    /**
     * set the camera to follow an object
     * @param object the object to follow or nullptr to stop following
     */
    void setToFollow(std::vector<MovingMapObject *> objectToWatch);

    /**
     * update the camera position and zoom
     * @param window the window to update
     */
    void update(sf::Time deltaTime);

   const sf::View &getView() const;

private:

    /**
     * the object that the camera is following
     */
    std::vector<MovingMapObject *> m_objectsToWatch;

    /**
     * the view of the camera
     */
    sf::View m_view;
    sf::Vector2f screenSize;

};