#pragma once
#include <functional>
#include <memory>
#include "MapObject/Character.h"
#include "Weapon/Weapon.h"
#include "Weapon/Gun.h"

/**
 * the class that represents the rifle weapon
 */
class Rifle : public Gun
{
public:
    /**
     * regular constructor
     * @param owner the owner of the weapon
     * @param addMapObjectFunc the function to add map objects to the map 
     *                         (bullets)
     * @param map the game map
     * @param bombHandler the bomb handler
     */
    Rifle(const Character &owner,
          GameHelperData &gameHelperData);
    
    /**
     * handle the mouse pressed event (shoot)
     * @param mousePosition the mouse position
     */
    void handleMousePressed(const MapVector &mousePosition) override;
    
    
private:
    
    /**
     * the character that holds the weapon
     */
    const Character &m_character;
};