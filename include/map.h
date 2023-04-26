#pragma once

#include <SFML/Graphics.hpp>
#include "map_vector.h"

/**
 * a class that represents the map of the game
 * using for both:
 * 
 * 1. calculate the collision of the objects with the map
 * 2. draw the map on the window
 */
class Map : public sf::Drawable
{
public:
    //todo: maybe change from consts to the size of the mask
    static const int WIDTH = 1080;
    static const int HEIGHT = 720;

    /**
     * create a map from the given images
     * @param mask black and white image that represents the map
     * @param sky image of the sky
     * @param ground image of the ground
     */
    Map(const sf::Image &mask, const sf::Image &sky, const sf::Image &ground);

    /**
     * get the mask of the map
     * @return the mask of the map
     */
    [[nodiscard]] const sf::Image *get_mask() const;

    /**
     * draw the map on the given target (window)
     * @param target the target to draw on
     * @param states the states of the target
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /**
     * draw a circle on the map
     * @param pos the position of the circle
     * @param radius the radius of the circle
     */
    void drawCircle(MapVector pos, int radius);
    
private:
    /**
     * the mask of the map
     */
    sf::Image m_mask;
    
    /**
     * the image of the sky
     */
    sf::Image m_sky;
    
    /**
     * the image of the ground
     */
    sf::Image m_ground;
    
    /**
     * the image that is displayed on the screen
     */
    sf::Image m_display;
};