#include <iostream>
#include "MapObject/Ball.h"

Ball::Ball(sf::Vector2f pos, GameMap *map, BombHandler *bomb_handler) :
        MovingMapObject(200, pos, map, 10,{0,0}, bomb_handler),
        m_numOfBounces(0),
        m_texture(PlayerColor::RED, 10)
{

}

void Ball::update(float delta_time)
{
    MovingMapObject::update(delta_time);
    std::cout << "rotation: " << getRotation() << std::endl;  
    m_texture.setAngle(getRotation());
}

void Ball::onDeath()
{
    std::cout << "Ball died" << std::endl;
}

bool Ball::collide(MovingMapObject *otherObject)
{
    return otherObject->collideDD(this);
}

bool Ball::collideDD(Ball *other_object)
{
    if(++m_numOfBounces > 5)
    {
        kill();

    }
    if(++(other_object->m_numOfBounces) > 5)
    {
        other_object->kill();
    }
    collideGeneric(other_object);
    MapVector center = (getPosition() + other_object->getPosition()) / 2.0f;
    addBomb({center, 100, 700});
//    sf::Vector2f center = (get_position() + otherObject->get_position()) / 2.0f;
    
    //todo: fix the problem of unrest the objects in the circle!
    //maybe to create another class for bombings?
//    addBomb({get_position(), 20, 7000});
    return true;
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    states.transform.rotate(getRotation());
    target.draw(m_texture, states);
}
