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
    
    /**
     * set the life level of the player (for the life bar)
     * @param life how much life the player has (in [0-1])
     */
    void setLife(float life);
    
    /**
     * set the angle of the player
     * @param angle the angle of the player (in radians)
     */
    void setAngle(float angle);
    
    /**
     * draw the player
     * @param target the target to draw to
     * @param states the states to draw with
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
private:
    /**
     * the sprite of the player himself
     */
    sf::Sprite m_sprite;
    
    /**
     * the life bar of the player with the current life level
     */
    
    sf::RectangleShape m_lifeBar;
    /**
     * the shield bar of the player with the current shield level
     */
    sf::RectangleShape m_shieldBar;
    /**
     * the life bar of the player with the full life level (black) 
     * for the background
     */
    sf::RectangleShape m_fullLifeBar;
    
    /**
     * the angle of the player (in degrees)
     */
    float m_angle;
    
    /**
     * the radius of the player shape (used for scaling)
     */
    float m_radius;
};