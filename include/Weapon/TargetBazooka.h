#pragma once
#include "Weapon/Weapon.h"
#include "MapObject/MovingMapObject.h"
#include "Weapon/Textures/GunTexture.h"

class TargetBazooka: public Weapon
{
public:
    TargetBazooka(const Character &owner,
                  GameHelperData &gameHelperData);

    void handleMousePressed(const MapVector &mousePosition) override;
    
    void update(const sf::Time &deltaTime) override;
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
private:
    Missile *m_missile;
    const Character &m_character;
    GunTexture m_texture;
    
    const static float MAX_ANGLE_DIFF; // max rotation speed in radians/sec

};
