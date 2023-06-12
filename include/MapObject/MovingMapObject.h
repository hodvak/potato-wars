#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <optional>
#include "BombHandler.h"
#include "MapVector.h"
#include "GameMap.h"

class Character;
class Projectile;
class Rock;
class BombObject;

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
     * @param weight the weight of the object
     * @param pos the start position of the object
     * @param radius the radius of the object
     * @param start_velocity the start velocity of the object
     * @param bomb_handler the bomb handler of the game
     */
    MovingMapObject(float weight,
                    MapVector pos,
                    GameMap *map,
                    float radius,
                    MapVector start_velocity = {0, 0},
                    BombHandler *bomb_handler = nullptr);


    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
     

    /**
     * update the velocity and the position of the object according to the forces
     * if override, the derived class should call this function first
     * @param deltaTime the time since the last update
     */
    virtual void update(const sf::Time &deltaTime);

    /**
     * update the object's velocity based on the collision with another object
     * @param other_object the object that the object collided with
     * @return true if the function did something, false otherwise (and then
     *         the other object should handle the collision)
     */
    virtual bool collisionObject(MovingMapObject *other_object);

    /**
     * get the velocity of the object
     */
    [[nodiscard]] MapVector getVelocity() const;

    /**
     * get the position of the object
     */
    [[nodiscard]] MapVector getPosition() const;

    /**
     * get the forces acting on the object
     */
    [[nodiscard]] MapVector getForces() const;

    /**
     * get the radius of the object
     */
    [[nodiscard]] float getRadius() const;

    /**
     * is the object still alive
     */
    [[nodiscard]] bool isAlive() const;

    /**
     * is the object still moving
     */
    [[nodiscard]] bool isRest() const;

    /**
     * get the rotation of the object (in radians)
     */
    [[nodiscard]] float getRotation() const;

    /**
     * getter for the map
     */
    [[nodiscard]] const GameMap *getMap() const;

    /**
     * check if 2 objects intersect
     * @param other_object the other object
     * @return is there an intersection
     */
    [[nodiscard]] bool intersect(const MovingMapObject &other_object) const;


    /**
     * kill the object
     */
    void kill();
    /**
     * stop the object
     */
    void stop();
    
    // ==================== collision functions ====================
    
    /**
     * collide function test for collision with other object and react 
     * accordingly using double dispatch, if both object didn't react, the
     * default reaction is to do generic collision
     * @param other_object 
     */
    void collide(MovingMapObject *other_object);
    /**
     * collideDD1 function for double dispatch
     * mus be implemented in the derived class as follows:
     * ```
     * bool collideDD1(ClassName *other_object)
     * {
     *     return other_object->collideDD2(this);
     * }
     * ```
     */     
    virtual bool collideDD1(MovingMapObject *other_object) = 0;
    
    /**
     * collideDD1 with double dispatch with the other objects
     */
    // with Character
    virtual bool collideDD2(Character *other_object);
    
    // with Projectile
    virtual bool collideDD2(Projectile *other_object);

    // with Rock
    virtual bool collideDD2(Rock *other_object);
    
    // with BombObject
    virtual bool collideDD2(BombObject *other_object);

    /**
     * handle the collision physically with the other object
     */
    void collideGeneric(MovingMapObject *other_object);
    
    // ==================== end of collision functions ====================

    /**
     * virtual destructor for the derived classes
     */
    ~MovingMapObject() override = default;

    /**
     * explode the object with the bomb
     * @param bomb the bomb that exploded
     */
    virtual void exploded(const Bomb &bomb);

/**
 * set the position of the object
 * @param pos the new position of the object
 */
void setPosition(MapVector pos);

/**
 * set the velocity of the object
 * @param velocity the new velocity of the object
 */
void setVelocity(MapVector velocity);

/**
 * get movement time
 */
[[nodiscard]] sf::Time getMovementTime() const;

private:

    /**
     * the rotation of the object (in radians)
     */
    float m_rotation;
    
    /**
     * the bomb handler of the game
     */
    BombHandler *m_bombHandler;
    
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
     * the current position of the object
     */
    MapVector m_pos;

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
     * the map that the object is on
     */
    GameMap *m_map;
    /**
     * a point that followes the object
     * and stops it when it get stucks
     */
    MapVector m_stuckPoint;
    /**
     * the time the stuck point is in the object radius
     */
    sf::Time m_movementTime;


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
     * set the forces acting on the object
     * @param forces the new forces acting on the object
     */
    void setForces(MapVector forces);

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
    void updateRotation(const sf::Time &deltaTime);


    /**
     * set the rotation of the object
     * @param rotation the new rotation of the object
     */
    void setRotation(float rotation);
    
    /**
     * add a bomb to the bomb handler
     * @param bomb the bomb to add
     */
    void addBomb(const Bomb &bomb);

};