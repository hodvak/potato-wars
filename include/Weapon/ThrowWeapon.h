#pragma once

#include <optional>
#include <functional>
#include <memory>

#include "Weapon/Weapon.h"
#include "Weapon/Textures/ThrowWeaponTexture.h"
#include "MapObject/MovingMapObject.h"

/**
 * the class that represents the throw weapon
 * can throw any MovingMapObject (bomb, rocket, etc.)
 */
class ThrowWeapon : public Weapon
{
public:
    
    /**
     * regular constructor
     * @param character the character that throws the weapon
     * @param weapon the weapon to throw
     * @param addMapObjectFunc the function to add map objects to the map
     */
    ThrowWeapon(const Character &character,
                std::unique_ptr<MovingMapObject> &&weapon,
                const std::function<void(std::unique_ptr<MovingMapObject> &&)>
                &addMapObjectFunc
    );

    /**
     * handle the mouse moved event
     * @param mousePosition the mouse position
     */
    void handleMouseMoved(const MapVector &mousePosition) override;
    
    /**
     * handle the mouse pressed event
     * @param mousePosition the mouse position
     */
    void handleMousePressed(const MapVector &mousePosition) override;

    /**
     * update the weapon
     * @param deltaTime the time passed since the last update
     */
    void update(const sf::Time &deltaTime) override;

    /**
     * draw the weapon on the target
     * @param target the target to draw on
     * @param states the states to draw with
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:

    /**
     * max distance of the mouse from the character to throw the weapon
     */
    const float MAX_MOUSE_DISTANCE = 100;
    
    /**
     * fix the position of the weapon by the character
     */
    void fixPosition();

    /**
     * the character that holds the weapon
     */
    const Character &m_character;
    
    /**
     * the weapon to throw
     */
    std::unique_ptr<MovingMapObject> m_weapon;
    
    /**
     * the start velocity of the weapon if it's thrown
     */
    MapVector m_startVelocity;
    
    /**
     * the function to add map objects to the map (to add the thrown weapon)
     */
    std::function<void(std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
    
    /**
     * the texture of the weapon
     */
    ThrowWeaponTexture m_texture;
};