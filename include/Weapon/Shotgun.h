#pragma once

#include <functional>
#include <memory>
#include "MapObject/Character.h"
#include "Weapon/Weapon.h"
#include "Weapon/Gun.h"


class Shotgun : public Gun
{
public:
    
    Shotgun(const Character &owner,
            GameHelperData &gameHelperData);

    
    void handleMousePressed(const MapVector &mousePosition) override;

private:
    const Character &m_character;

    constexpr static const int BULLETS_COUNT = 10;
    constexpr static const float BULLETS_ANGLE =  0.4712f; // 0.15 * PI
};