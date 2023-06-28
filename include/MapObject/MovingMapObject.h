#pragma once

#include <memory>
#include <optional>
#include <SFML/Graphics.hpp>
#include "BombHandler.h"
#include "MapVector.h"
#include "GameMap.h"
#include "GameHelperData.h"

class Character;

class Projectile;

class Rock;

class Bomb;

class HealthCrate;

class WeaponCrate;

class Missile;

class Fragments;

/**
 * all object in the game are derived from this class.
 * this class know to draw the object, and to update it's position according to
 * the forces acting on it.
 */
class MovingMapObject : public sf::Drawable
{
public:
    /**
     * regular constructor
     * @param pos the start position of the object
     * @param radius the radius of the object
     * @param weight the weight of the object
     * @param gameHelperData the gameHelperData of the game
     * @param startVelocity the start velocity of the object
     */
    MovingMapObject(const MapVector &pos,
                    float radius,
                    float weight,
                    GameHelperData &gameHelperData,
                    const MapVector &startVelocity = {0, 0});


    /**
     * update the velocity and the position of the object according to the forces
     * if override, the derived class should call this function first
     * @param deltaTime the time since the last update
     */
    virtual void update(const sf::Time &deltaTime);

    // ==================== getters ====================
    /**
     * get the velocity of the object
     */
    [[nodiscard]] const MapVector &getVelocity() const;

    /**
     * get the position of the object
     */
    [[nodiscard]] const MapVector &getPosition() const;

    /**
     * get the forces acting on the object
     */
    [[nodiscard]] const MapVector &getForces() const;

    /**
     * get the radius of the object
     */
    [[nodiscard]] float getRadius() const;

    /**
     * get the rotation of the object (in radians)
     */
    [[nodiscard]] float getRotation() const;


    /**
     * getter for the stuck point
     */
    [[nodiscard]] const MapVector &getStuckPoint() const;

    /**
     * get the GameHelperData of the game
     */
    [[nodiscard]] GameHelperData &getGameHelperData() const;

    /**
     * is the object still alive
     */
    [[nodiscard]] bool isAlive() const;

    /**
     * is the object still moving
     */
    [[nodiscard]] bool isRest() const;

    // ================= end of getters =================

    // ==================== setters ====================
    /**
     * set the position of the object
     * @param pos the new position of the object
     */
    void setPosition(const MapVector &pos);

    /**
     * set the velocity of the object
     * @param velocity the new velocity of the object
     */
    void setVelocity(const MapVector &velocity);


    /**
     * set the forces acting on the object
     * @param forces the new forces acting on the object
     */
    void setForces(const MapVector &forces);

    /**
     * get movement time
     */
    [[nodiscard]] const sf::Time &getMovementTime() const;

    /**
     * kill the object
     */
    void kill();

    /**
     * stop the object (set the `inRest` to true)
     */
    void stop();


    // ==================== collision functions ====================

    /**
     * collide function test for collision with other object and react 
     * accordingly using double dispatch, if both object didn't react, the
     * default reaction is to do generic collision
     * @param other_object 
     */
    void collide(MovingMapObject &otherObject);

    /**
     * collideDD1 function for double dispatch
     * mus be implemented in the derived class as follows:
     * ```
     * bool collideDD1(MovingMapObject &otherObject)
     * {
     *     return otherObject.collideDD2(*this);
     * }
     * ```
     */
    virtual bool collideDD1(MovingMapObject &otherObject) = 0;

    /**
     * collideDD1 with double dispatch with the other objects
     */
    // with Character
    virtual bool collideDD2(Character &otherObject);

    // with Projectile
    virtual bool collideDD2(Projectile &otherObject);

    // with Rock
    virtual bool collideDD2(Rock &otherObject);

    // with Bomb
    virtual bool collideDD2(Bomb &otherObject);

    // with HealthCrate
    virtual bool collideDD2(HealthCrate &otherObject);
    
    // with WeaponCrate
    virtual bool collideDD2(WeaponCrate &otherObject);

    // with Missile
    virtual bool collideDD2(Missile &otherObject);

    //WITH Fragments
    virtual bool collideDD2(Fragments &otherObject);

    /**
     * handle the collision physically with the other object
     */
    void collideGeneric(MovingMapObject &otherObject);


    /**
     * is the object a collision object with generic collision if None of the
     * other collideDD functions were implemented
     */
    [[nodiscard]] virtual bool collisionObject() const;

    /**
     * check if 2 objects intersect
     * @param other_object the other object
     * @return is there an intersection
     */
    [[nodiscard]] bool intersect(const MovingMapObject &otherObject) const;

    // ==================== end of collision functions ====================

    /**
     * explode the object with the BOMB
     * @param bomb the BOMB that exploded
     */
    virtual void exploded(const Explosion &bomb);


    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void unrest();


protected:

    /**
     * set the forces according to the delta time.
     * by default, the forces are only the gravity
     * @param deltaTime the time since the last update
     */
    virtual void updateForces(const sf::Time &deltaTime);

    /**
     * by default update the velocity of the object according to the forces
     * acting on it
     * @param deltaTime the time since the last update
     */
    virtual void updateVelocity(const sf::Time &deltaTime);

    /**
     * by default update the position of the object according to the velocity
     * @param deltaTime the time since the last update
     */
    virtual void updatePosition(const sf::Time &deltaTime);

    /**
     * override this function to do something when the object is killed (will
     * only be called once)
     */
    virtual void onDeath()
    {};


    /**
     * update the object's velocity based on the collision with the map
     * @param angle angle of the collision with the map
     * @return the hit angle of the collision if the object collideDD1 with the map
     */
    virtual std::optional<float> collisionMap();

    /***
     * update the object rotation angle according to the velocity
     */
    virtual void updateRotation(const sf::Time &deltaTime);


    /**
     * set the rotation of the object
     * @param rotation the new rotation of the object
     */
    void setRotation(float rotation);


private:

    // ======= private member variables =======
    /**
     * the current position of the object
     */
    MapVector m_pos;


    /**
     * the rotation of the object (in radians)
     */
    float m_rotation;
    
    /**
     * the data of the game
     */
    GameHelperData &m_gameHelperData;

    /**
     * the weight of the object
     */
    float m_weight;

    /**
     * the forces acting on the object
     */
    MapVector m_forces;

    /**
     * the current velocity of the object
     */
    MapVector m_velocity;

    /**
     * the radius of the object
     */
    float m_radius;

    /**
     * is the object resting on the ground and not need to be updated
     */
    bool m_resting;

    /**
     * is the object is still alive
     */
    bool m_alive;

    /**
     * a point that follows the object
     * and stops it when it get stacks
     */
    MapVector m_stuckPoint;
    /**
     * the time the stuck point is in the object radius
     */
    sf::Time m_movementTime;

};