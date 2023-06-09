#pragma once
#include <SFML/Graphics.hpp>
#include "MapObject/Character.h"
class ThrowWeaponTexture: public sf::Drawable
{
public:
    explicit ThrowWeaponTexture(const Character &character,
                                const MapVector &direction,
                                float maxDistance = 100);
    
    void update(const sf::Time &deltaTime);
    
    void setDirection(const MapVector &direction);
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    const Character &m_character;
    MapVector m_direction;
    float m_maxDistance;

};