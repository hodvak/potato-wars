#pragma once

#include "MapVector.h"
#include "PlayerColor.h"

/**
 * class that draws the rifle (and the aim) of the player
 */
class GunTexture : public sf::Drawable
{
public:
    GunTexture(const sf::Vector2f &gunPosition,
               float gunRadius,
               const sf::Texture &gunTexture,
               const sf::IntRect &textureRect,
               const sf::Vector2f &aimPosition,
               float aimRadius);
    
    
    /**
     * set the position of the gun (the center of the character)
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
     * fix the rotation of the gun
     */
    void fixRotation();
    
    /**
     * the sprite of the gun
     */
    sf::Sprite m_gunSprite;
    
    /**
     * the sprite of the aim
     */
    sf::Sprite m_aimSprite;
};