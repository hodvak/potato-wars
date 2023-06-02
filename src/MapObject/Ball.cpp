#include <iostream>
#include "MapObject/Ball.h"

Ball::Ball(sf::Vector2f pos,
           GameMap *map,
           BombHandler *bomb_handler,
          PlayerColor color
           ) :
        MovingMapObject(200, pos, map, 10,{0,0}, bomb_handler),
        m_life(1),
        m_texture(color, 10)
{

}

void Ball::update(float delta_time)
{
    MovingMapObject::update(delta_time);
    if(isRest())
    {
        setRotation(0);
    }
    m_texture.setAngle(getRotation() * 180/ MapVector::PI);
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
    damage(0.1f);
    other_object->damage(0.1f);
    collideGeneric(other_object);
    MapVector center = (getPosition() + other_object->getPosition()) / 2.0f;
    addBomb({center, 100, 700});
    return true;
}

void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    target.draw(m_texture, states);
}

void Ball::damage(float damage)
{
    m_life -= damage;
    if(m_life <= 0)
    {
        kill();
    }
    m_texture.setLife(m_life);
}
