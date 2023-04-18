#include <iostream>
#include "ball.h"


Ball::Ball(sf::Vector2f pos, sf::Image *map, BombHandler *bombHandler) :
    MovingMapObject(200, pos, map, 10,{0,0}, bombHandler),
    m_numOfBounces(0)
{
}

float Ball::collision_map()
{
    float angle = MovingMapObject::collision_map();
    return angle;
}

void Ball::update(float deltaTime, sf::Image &map)
{
    MovingMapObject::update(deltaTime, map);
}

void Ball::on_death()
{
    std::cout << "Ball died" << std::endl;
}

bool Ball::collide(MovingMapObject *otherObject)
{
    return otherObject->collide_dd(this);
}

bool Ball::collide_dd(Ball *otherObject)
{
    if(++m_numOfBounces > 5)
    {
        kill();
    }
    if(++(otherObject->m_numOfBounces) > 5)
    {
        otherObject->kill();
    }
    collide_generic(otherObject);
    sf::Vector2f center = (get_position() + otherObject->get_position()) / 2.0f;
    
    //todo: fix the problem of unrest the objects in the circle!
    //maybe to create another class for bombings?
    addBomb({get_position(), 100, 7000});
    return true;
}
