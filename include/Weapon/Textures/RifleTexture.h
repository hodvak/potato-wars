#pragma once

#include "MapVector.h"
#include "PlayerColor.h"

/**
 * class that draws the rifle (and the aim) of the player
 */
class RifleTexture : public sf::Drawable
{
public:
    /**
     * regular constructor
     * @param color the color of the player
     * @param position the position of the player
     * @param aimPosition the position of the aim
     * @param radius the radius of the aim
     */
    RifleTexture(PlayerColor color, 
                 const MapVector &position,
                 const MapVector &aimPosition, 
                 float radius);
    
    /**
     * set the position of the rifle (the center of the character)
     * @param position the position of the rifle
     */
    void setPosition(const MapVector &position);
    
    /**
     * set the position of the aim (the mouse position)
     * @param aimPosition the position of the aim
     */
    void setAimPosition(const MapVector &aimPosition);
    
    /**
     * draw the rifle and the aim on the target
     * @param target the target to draw on
     * @param states the states to draw with
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
private:
    /**
     * the color of the player
     */
    PlayerColor m_color;
    
    /**
     * the position of the rifle
     */
    MapVector m_position;
    
    /**
     * the position of the aim
     */
    MapVector m_aimPosition;
    
    /**
     * the radius of the rifle
     */
    float m_radius;
};