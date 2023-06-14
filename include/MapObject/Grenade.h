#pragma once

#include "MapObject\MovingMapObject.h"

class Grenade : public MovingMapObject
{
public:
    Grenade(MapVector pos, GameMap *map, BombHandler *bombHandler);

    void update(const sf::Time &deltaTime) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        sf::CircleShape shape(getRadius());
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(getPosition().x - getRadius(), getPosition().y - getRadius());
        target.draw(shape, states);
    }

    bool collideDD1(MovingMapObject *other_object) override
    {
        return other_object->collideDD2(this);
    }


private:
    float m_timeToExplosion;
    bool m_pinIsOut = false;
};

