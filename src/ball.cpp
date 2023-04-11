#include <iostream>
#include "ball.h"


Ball::Ball(sf::Vector2f pos, sf::Image *map) :
    MovingMapObject(200, pos, map, 10),
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
    
    for(int i = -20; i < 20; i++)
    {
        for (int j = -20; j < 20; ++j)
        {
            if(i * i + j * j < 400)
            {
                sf::Vector2i pos = {(int) center.x + i, (int) center.y + j};
                if(pos.x >= 0 && pos.x < get_map()->getSize().x && pos.y >= 0 && pos.y < get_map()->getSize().y)
                {
                    get_map()->setPixel(pos.x, pos.y, sf::Color::Black);
                }
            }
        }
    }
    return true;
}
