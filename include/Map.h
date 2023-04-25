#pragma once

#include <SFML/Graphics.hpp>
#include "MapVector.h"

class Map : public sf::Drawable
{
public:
    //todo: maybe change from consts to the size of the mask
    static const int WIDTH = 1080;
    static const int HEIGHT = 720;

    Map(const sf::Image &mask, const sf::Image &sky, const sf::Image &ground);

    const sf::Image *getMask() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void drawCircle(MapVector pos, int radius);
    
private:
    sf::Image m_mask;
    sf::Image m_sky;
    sf::Image m_ground;
    sf::Image m_display;
};