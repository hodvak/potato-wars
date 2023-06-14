#include "MapObject/Grenade.h"

Grenade::Grenade(MapVector pos, GameMap *map, BombHandler *bombHandler) :
        MovingMapObject(1, pos, map, 10, {0, 0}, bombHandler),
        m_timeToExplosion(3)
{

}

void Grenade::update(const sf::Time &deltaTime)
{
    MovingMapObject::update(deltaTime);
    if(!isRest())
    {
        m_pinIsOut = true;
    }
    if(m_pinIsOut)
    {
        m_timeToExplosion -= deltaTime.asSeconds();
        if(m_timeToExplosion <= 0)
        {
            kill();
            addBomb({getPosition(), 30, 100});
        }
    }
}
