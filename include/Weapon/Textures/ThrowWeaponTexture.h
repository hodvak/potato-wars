#pragma once

#include <SFML/Graphics.hpp>
#include "MapObject/Character.h"

/**
 * the class that draws the throw weapon texture
 * can throw any MovingMapObject (bomb, rocket, etc.)
 */
class ThrowWeaponTexture: public sf::Drawable
{
public:
    /**
     * regular constructor
     * @param character the character that throws the weapon
     * @param direction the direction to throw the weapon
     * @param maxDistance the max distance to throw the weapon
     */
    explicit ThrowWeaponTexture(const Character &character,
                                const MapVector &direction,
                                float maxDistance = 100);
    
    /**
     * update the texture
     * @param deltaTime the time passed since the last update
     */
    void update(const sf::Time &deltaTime);
    
    /**
     * set the direction to throw the weapon
     * @param direction the direction to throw the weapon
     */
    void setDirection(const MapVector &direction);
    
    /**
     * draw the texture on the target
     * @param target the target to draw on
     * @param states the states to draw with
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    const Character &m_character;
    MapVector m_direction;
    float m_maxDistance;

};