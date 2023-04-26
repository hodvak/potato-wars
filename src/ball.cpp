#include <iostream>
#include "ball.h"


Ball::Ball(sf::Vector2f pos, Map *map, BombHandler *bomb_handler) :
    MovingMapObject(200, pos, map, 10,{0,0}, bomb_handler),
    m_num_of_bounces(0),
    m_texture(PlayerColor::RED, 10)
{
}

void Ball::update(float delta_time)
{
    MovingMapObject::update(delta_time);
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
    if(++m_num_of_bounces > 5)
    {
        kill();
    }
    if(++(otherObject->m_num_of_bounces) > 5)
    {
        otherObject->kill();
    }
    collide_generic(otherObject);
    MapVector center = (get_position() + otherObject->get_position()) / 2.0f;
    add_bomb({center, 100, 700});
//    sf::Vector2f center = (get_position() + otherObject->get_position()) / 2.0f;
    
    //todo: fix the problem of unrest the objects in the circle!
    //maybe to create another class for bombings?
//    addBomb({get_position(), 20, 7000});
    return true;
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(get_position());
    target.draw(m_texture, states);
}
