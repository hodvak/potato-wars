#pragma once

#include <SFML/Graphics.hpp>
#include "MapVector.h"
#include "ParallaxLayer.h"

/**
 * a class that represents the map of the game
 * using for both:
 * 
 * 1. calculate the collision of the objects with the map
 * 2. draw the map on the window
 */
class GameMap : public sf::Drawable
{
public:
    /**
     * regular constructor
     * @param levelName the name of the level to load
     */
    explicit GameMap(int levelNumber);

    /**
     * get the mask of the map, used for collision detection
     * @return the mask of the map
     */
    [[nodiscard]] const sf::Image &getMask() const;

    /**
     * change the map (mask) according to the explosion
     * @param pos the position of the explosion
     * @param radius the radius of the explosion
     */
    void bomb(const MapVector &pos, int radius);

    /**
     * draw the map on the target
     * @param target the target to draw on
     * @param states the states to draw with
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(const sf::Time &deltaTime);
    void setTarget(const sf::RenderTarget *target);


private:
    
/**
     * the width of the map
     */
    unsigned int m_width;
    
    /**
     * the height of the map
     */
    unsigned int m_height;
    
    /**
     * the mask of the map
     */
    sf::Image m_mask;
    
    /**
     * image of the sky and the ground
     */
    const sf::Image *m_sky;
    const sf::Image *m_ground;
    
    /**
     * image to display on 'draw' function
     */
    sf::Image m_display;

    /**
     * the layers of the map
     */
    std::vector<ParallaxLayer> m_layers;
};