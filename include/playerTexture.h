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
    
    void setLife(float life);
    
    void setAngle(float angle);
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
private:
    sf::Sprite m_sprite;
    sf::RectangleShape m_lifeBar;
    sf::RectangleShape m_fullLifeBar;
    float m_angle;
    float m_radius;
};