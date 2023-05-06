#pragma once

#include <SFML/Graphics.hpp>
#include "MovingMapObject.h"

/**
 * a class that handle camera movement, focus and zoom
 */
class Camera
{
public:
    /**
     * regular constructor
     */
    Camera();

    /**
     * set the camera to follow an object
     * @param object the object to follow or nullptr to stop following
     */
    void setToFollow(MovingMapObject *object);

    /**
     * update the camera position and zoom
     * @param window the window to update
     */
    void update(sf::RenderWindow *window);

private:

    /**
     * the object that the camera is following
     */
    MovingMapObject *m_object = nullptr;

    /**
     * the view of the camera
     */
    sf::View m_view;

};