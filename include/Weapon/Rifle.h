#pragma once
#include <functional>
#include <memory>
#include "MapObject/Character.h"
#include "Weapon/Weapon.h"
#include "Weapon/Textures/RifleTexture.h"

/**
 * the class that represents the rifle weapon
 */
class Rifle : public Weapon
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
          const std::function<void(std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
          const GameMap &map,
          BombHandler &bombHandler);

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
     * draw the weapon on the target
     * @param target the target to draw on
     * @param states the states to draw with
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    /**
     * update the weapon
     * @param deltaTime the time passed since the last update
     */
    void update(const sf::Time &deltaTime) override;
    
private:
    
    /**
     * the position to aim at
     */
    MapVector m_aimPosition;
    
    /**
     * the character that holds the weapon
     */
    const Character &m_character;
    
    /**
     * the texture of the weapon
     */
    RifleTexture m_texture;
    
    /**
     * the function to add map objects to the map (bullets)
     */
    std::function<void(std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
    
    /**
     * the game map
     */
    const GameMap &m_map;
    
    /**
     * the bomb handler
     */
    BombHandler &m_bombHandler;
};