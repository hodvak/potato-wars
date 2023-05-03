#pragma once

#include "moving_map_object.h"
#include "map.h"

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
     */
    Ball(sf::Vector2f pos, Map *map, BombHandler *bomb_handler);
    
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
    bool collide_dd(Ball *other_object) override;
    
    /**
     * print the message "Ball died" to the console
     */
    void on_death() override;


private:
    
    /**
     * the number of bounces the Ball did
     */
    int m_num_of_bounces;



};