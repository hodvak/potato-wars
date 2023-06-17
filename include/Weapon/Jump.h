#pragma once

#include "ThrowWeapon.h"

/***
 * the class that represents the jump weapon
 * let the charecter jump (throw himself)
 */
class Jump : public ThrowWeapon
{
public:
    Jump(Character &character,const std::function<void(std::unique_ptr<MovingMapObject> &&)>
    &addMapObjectFunc);
    void handleMousePressed(const MapVector &mousePosition) override;
private:
    /**
     * max distance of the mouse from the character to throw the weapon
     */
    static constexpr double MAX_MOUSE_DISTANCE = 100;
    Character &m_character;

};