#pragma once

#include "MovingMapObject.h"
#include "GameMap.h"
#include "playerTexture.h"

/**
 * a Ball is a test for MovingMapObject
 * after it bounces 5 times it dies
 * todo: remove this class when it is no longer needed
 */
class Ball : public MovingMapObject
{
public:
    /**
     * create a Ball in the given position
     * @param pos the position of the Ball
     * @param map the map that the Ball is in
     * @param bomb_handler BombHandler to add bombs to
     * @param color the color of the Ball (Player)
     */
    Ball(sf::Vector2f pos,
         GameMap *map,
         BombHandler *bomb_handler,
         PlayerColor color);
    
    /**
     * update the Ball according to the time that passed
     * @param deltaTime the time that passed since the last update
     */
    void update(float delta_time) override;
    
    /**
     * function for double dispatch. need to be the same in all the 
     * MovingMapObject derived classes
     */
    bool collide(MovingMapObject *other_object) override;
    
    /**
     * collide with a Ball. add the counter and kill the Ball if needed
     */
    bool collideDD(Ball *other_object) override;
    
    /**
     * print the message "Ball died" to the console
     */
    void onDeath() override;
    
    /**
     * decrease the life of the Player
     * @param damage the amount of life to decrease
     */
    void damage(float damage);
    
     

    /**
     * draw the Ball to the target
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    
    /**
     * texture of the Player
     */
    PlayerTexture m_texture;
    
    /**
     * life of the player (between 0 and 1)
     */
    float m_life;

};