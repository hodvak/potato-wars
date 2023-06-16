#pragma once
#include "MapObject/MovingMapObject.h"

/**
 * class that represents a projectile in the game, (only bullet for now)
 * the projectile will die when it hits a wall or a character (and deal damage
 * and create an explosion)
 */
class Projectile : public MovingMapObject
{
public:
    
    /**
     * create a projectile in the given position
     * @param weight the weight of the projectile
     * @param pos the position of the projectile
     * @param radius the radius of the projectile 
     * @param damage the damage that the projectile will deal
     * @param startVelocity the start velocity of the projectile
     * @param map the map that the projectile is in
     * @param bombHandler the bomb handler of the game 
     */
    Projectile(float weight,
               const MapVector &pos,
               float radius,
               float damage,
               const MapVector &startVelocity,
               const GameMap &map,
               BombHandler &bombHandler);

    /**
     * update the projectile according to the time that passed
     * and explode if it hit a wall
     * @param deltaTime the time that passed since the last update
     */
    void update(const sf::Time &deltaTime) override;
    
    /**
     * function for double dispatch. need to be the same in all the 
     * MovingMapObject derived classes
     */
    bool collideDD1(MovingMapObject &otherObject) override;
    
    /**
     * collide Double Dispatch with a Character.
     * will deal damage to the character and explode
     */
    bool collideDD2(Character &otherObject) override;
    
    /**
     * draw the projectile on the target
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    
    /**
     * the damage that the projectile will deal
     */
    float m_damage;
};