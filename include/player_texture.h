#pragma once

#include <SFML/Graphics.hpp>
#include "PlayerColor.h"

/**
 * a class that draws the player.
 */
class PlayerTexture : public sf::Drawable
{
public:
    /**
     * regular constructor
     * @param color the color of the player
     * @param radius the radius of the player shape
     */
    PlayerTexture(PlayerColor color, float radius);
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
private:
    sf::Sprite m_sprite;
};