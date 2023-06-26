#pragma once

#include "ThrowWeapon.h"

/***
 * the class that represents the jump weapon
 * let the charecter jump (throw himself)
 */
class Jump : public ThrowWeapon
{
public:
    Jump(Character &character,
         GameHelperData &gameHelperData);
    
    void handleMousePressed(const MapVector &mousePosition) override;
    
    [[nodiscard]] bool turnEnder() const override;
private:
    /**
     * max distance of the mouse from the character to throw the weapon
     */
    static constexpr double MAX_MOUSE_DISTANCE = 100;
    Character &m_character;

};