#include <iostream>
#include "ball.h"


Ball::Ball(sf::Vector2f pos) : 
    MovingMapObject(200, pos, 10),
    m_numOfBounces(0)
{
}

float Ball::collision_map(sf::Image &map)
{
    float angle = MovingMapObject::collision_map(map);
    if(angle != -1)
    {
        m_numOfBounces++;
    }
    if(m_numOfBounces > 10)
    {
//        this->kill();
    }
    return angle;
}

void Ball::update(float deltaTime, sf::Image &map)
{
    MovingMapObject::update(deltaTime, map);
//    if(is_rest())
//    {
//        kill();
//    }
}

void Ball::on_death()
{
    std::cout << "Ball died" << std::endl;
}

bool Ball::collide(MovingMapObject *otherObject)
{
    std::cout << "collision ball 1" << std::endl;
    return otherObject->collide_dd(this);
}

bool Ball::collide_dd(Ball *otherObject)
{
    std::cout << "collision ball 2" << std::endl;
    collide_generic(otherObject);
    return true;
}
