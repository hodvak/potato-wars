#pragma once

#include <SFML/Graphics.hpp>
#include "MapObject/MovingMapObject.h"

/**
 * a class that handle camera movement, focus and zoom
 * following a list of objects that are moving
 *
 * */
class ActionCamera
{
public:
    /**
     * regular constructor
     */
    ActionCamera(float width, float height);

    /**
     * set the camera to follow a list of objects
     * @param objectsToWatch the objects to follow
     */
    void setToFollow(std::vector<MovingMapObject *> &&objectsToWatch);

    /**
     * update the camera position and zoom
     * @param window the window to update
     */
    void update(sf::Time deltaTime);

    /**
     * get the view of the camera
     * @return the view of the camera
     */ 
   const sf::View &getView() const;

private:

    /**
     * the objects to follow
     */
    std::vector<MovingMapObject *> m_objectsToWatch;

    /**
     * the view of the camera
     */
    sf::View m_view;
    
    /**
     * the size of the screen
     */
    sf::Vector2f screenSize;

};