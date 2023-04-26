#pragma once
#include "MapVector.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "BombHandler.h"
#include "Map.h"

/**
 * the acceleration of all object due to gravity on our potato planet
 */
const float GRAVITY = 130;

/**
 * the friction (static and dynamic) of the ground on our potato planet
 */
const float FRICTION = 0.2f;

class Ball;

/**
 * all object in the game are derived from this class.
 * this class know to draw the object, and to update it's position according to
 * the forces acting on it.
 */
class MovingMapObject
{
public:
    /**
     * regular constructor
     * @param weight the weight of the object
     * @param pos the start position of the object
     * @param radius the radius of the object
     * @param startVelocity the start velocity of the object
     */
    MovingMapObject(float weight,
                    MapVector pos,
                    Map *map,
                    float radius,
                    MapVector startVelocity = {0, 0},
                    BombHandler *bombHandler = nullptr);


    /**
     * draw the object on the screen if it is visible
     * @param target the window to draw on
     * @param cameraRect what the camera sees
     */
    void draw(sf::RenderTarget &target,
              const sf::Rect<float> &cameraRect) const;

    /**
     * update the velocity and the position of the object according to the forces
     * if override, the derived class should call this function first
     * @param deltaTime the time since the last update
     */
    virtual void update(float deltaTime, Map *map);

    /**
     * update the object's velocity based on the collision with another object
     * @param otherObject the object that the object collided with
     * @return true if the function did something, false otherwise (and then
     *         the other object should handle the collision)
     */
    virtual bool collision_object(MovingMapObject *otherObject);

    /**
     * get the velocity of the object
     */
    [[nodiscard]] MapVector get_velocity() const;

    /**
     * get the position of the object
     */
    [[nodiscard]] MapVector get_position() const;

    /**
     * get the forces acting on the object
     */
    [[nodiscard]] MapVector get_forces() const;

    /**
     * get the radius of the object
     */
    [[nodiscard]] float get_radius() const;

    /**
     * is the object still alive
     */
    [[nodiscard]] bool is_alive() const;

    /**
     * is the object still moving
     */
    [[nodiscard]] bool is_rest() const;

    /**
     * kill the object
     */
    void kill();

    /**
     * collide function for double dispatch
     * mus be implemented in the derived class as follows:
     * ```
     * bool collide(ClassName *otherObject)
     * {
     *     return otherObject->collide_dd(this);
     * }
     */
    virtual bool collide(MovingMapObject *otherObject) = 0;

    /**
     * collide with double dispatch with the other objects
     */
    // with Ball
    virtual bool collide_dd(Ball *otherObject);

    /**
     * virtual destructor for the derived classes
     */
    virtual ~MovingMapObject() = default;

    /**
     * get the weight of the object
     */
    void exploded(const Bomb &bomb);

    void addBomb(const Bomb &bomb);

private:
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
    Map *m_map;

protected:

    /**
     * set the forces according to the delta time.
     * by default, the forces are only the gravity
     * @param deltaTime the time since the last update
     */
    virtual void update_forces(float deltaTime);

    /**
     * by default update the velocity of the object according to the forces
     * acting on it
     * @param deltaTime the time since the last update
     */
    virtual void update_velocity(float deltaTime);

    /**
     * by default update the position of the object according to the velocity
     * @param deltaTime the time since the last update
     */
    virtual void update_position(float deltaTime);

    /**
     * set the velocity of the object
     * @param velocity the new velocity of the object
     */
    void set_velocity(MapVector velocity);

    /**
     * set the position of the object
     * @param pos the new position of the object
     */
    void set_position(MapVector pos);

    /**
     * set the forces acting on the object
     * @param forces the new forces acting on the object
     */
    void set_forces(MapVector forces);

    /**
     * override this function to do something when the object is killed (will
     * only be called once)
     */
    virtual void on_death()
    {};

    /**
     * getter for the map
     */
    Map *get_map();

    /**
     * handle the collision physically with the other object
     */
    void collide_generic(MovingMapObject *otherObject);

    /**
     * update the object's velocity based on the collision with the map
     * @param angle angle of the collision with the map
     * @return the hit angle of the collision if the object collide with the map
     *         or -1 if the object is not colliding with the map
     */
    virtual float collision_map();

};