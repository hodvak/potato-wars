#pragma once
#include <functional>
#include <memory>
#include "MapObject/Character.h"
#include "Weapon/Weapon.h"
#include "Weapon/Gun.h"

/**
 * the class that represents the rifle weapon
 */
class Minigun : public Gun
{
public:
    Minigun(const Character &owner,
            GameHelperData &gameHelperData);

    
    void handleMouseMoved(const MapVector &mousePosition) override;
    
    void handleMousePressed(const MapVector &mousePosition) override;
    
    void update(const sf::Time &deltaTime) override;
    
private:
    
    const Character &m_character;
    
    MapVector m_aimPosition;
    
    sf::Time m_timePassed;
    
    bool m_firing;
    
    int m_bulletsFired;
    
    static const int BULLETS_COUNT = 8;
    constexpr static const float BULLETS_ANGLE =  0.157f; // 0.05 * PI
};