#include <numbers>
#include "MapObject/BombObject.h"


BombObject::BombObject(const MapVector &pos, GameMap *map,
                       BombHandler *bomb_handler):
        MovingMapObject(50, pos, map, 7, {0, 0}, bomb_handler),
        m_texture(7,sf::seconds(10)),
        m_time(sf::Time::Zero)
{

}

void BombObject::update(const sf::Time &deltaTime)
{
    MovingMapObject::update(deltaTime);
    m_time += deltaTime;
    m_texture.setReminingTime(sf::seconds(10) - m_time);
    if (m_time > sf::seconds(10))
    {
        addBomb({getPosition(), 50 , 3000});
        kill();
    }
    m_texture.setAngle(getRotation());
}

bool BombObject::collideDD1(MovingMapObject *other_object)
{
    return other_object->collideDD2(this);
}

bool BombObject::collideDD2(Character *other_object)
{
    addBomb({getPosition(), 50 , 3000});
    kill();
    return true;
}

void BombObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    target.draw(m_texture, states);
}

