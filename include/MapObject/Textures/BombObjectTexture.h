#pragma once

#include <SFML/Graphics.hpp>

/**
 * a class that manages the texture for the BOMB object in the game.
 */
class BombObjectTexture : public sf::Drawable
{
public:
    /**
     * regular constructor
     * @param radius the radius of the BOMB object
     * @param time the time until the BOMB explodes 
     */
    BombObjectTexture(float radius,const sf::Time &time);
    
    /**
     * set the time until the BOMB explodes
     * @param time the time until the BOMB explodes
     */
    void setRemainingTime(const sf::Time& time);
    
    /**
     * set the angle of the BOMB object
     * @param angle the angle of the BOMB object
     */
    void setAngle(float angle);
    
    /**
     * draw the BOMB object (pos will be given by the transform of the states)
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    

private:
    
    /**
     * the angle of the BOMB object
     */
    float m_angle;
    
    /**
     * the radius of the BOMB object
     */
    float m_radius;
    
    /**
     * the time until the BOMB explodes
     */
    sf::Time m_remainedTime;
};