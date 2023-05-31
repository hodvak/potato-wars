#pragma once

#include <SFML/Graphics.hpp>
#include "MapVector.h"

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
    explicit GameMap(const std::string &levelName);

    [[nodiscard]] const sf::Image &getMask() const;

    void bomb(MapVector pos, int radius);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


private:
    unsigned int m_width;
    unsigned int m_height;
    sf::Image m_mask;
    const sf::Image *m_sky;
    const sf::Image *m_ground;
    sf::Image m_display;
};