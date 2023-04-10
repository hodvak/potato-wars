#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

/**
 * the acceleration of all object due to gravity on our potato planet
 */
const float GRAVITY = 35;

/**
 * the friction (static and dynamic) of the ground on our potato planet
 */
const float FRICTION = 0.2;


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
                    sf::Vector2f pos,
                    float radius,
                    sf::Vector2f startVelocity = {0, 0});

    
    /**
     * draw the object on the screen if it is visible
     * @param target the window to draw on
     * @param cameraRect what the camera sees
     */
    void draw(sf::RenderTarget &target, sf::Rect<float> cameraRect) const;

    /**
     * update the velocity and the position of the object according to the forces
     * if override, the derived class should call this function first
     * @param deltaTime the time since the last update
     */
    virtual void update(float deltaTime);

    /**
     * update the object's velocity based on the collision with the map
     * @param angle angle of the collision with the map
     * @return the hit angle of the collision if the object collide with the map
     *         or -1 if the object is not colliding with the map
     */
    virtual float collision_map(sf::Image &map);
    
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
    sf::Vector2f get_velocity() const;
    
    /**
     * get the position of the object
     */
    sf::Vector2f get_position() const;
    
    /**
     * get the forces acting on the object
     */
    sf::Vector2f get_forces() const;
    
    /**
     * get the radius of the object
     */
    float get_radius() const;
    
    /**
     * virtual destructor for the derived classes
     */
    virtual ~MovingMapObject() = default;

private:
    /**
     * the weight of the object
     */
    float m_weight;
    
    /**
     * the forces acting on the object
     */
    sf::Vector2f m_forces;
    
    /**
     * the current velocity of the object
     */
    sf::Vector2f m_velocity;
    
    /**
     * the current position of the object
     */
    sf::Vector2f m_pos;
    
    /**
     * the radius of the object
     */
    float m_radius;
    
    /**
     * is the object resting on the ground and not need to be updated
     */
    bool resting;
    
    
    
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
    void set_velocity(sf::Vector2f velocity);
    
    /**
     * set the position of the object
     * @param pos the new position of the object
     */
    void set_position(sf::Vector2f pos);
    
    /**
     * set the forces acting on the object
     * @param forces the new forces acting on the object
     */
    void set_forces(sf::Vector2f forces);
};