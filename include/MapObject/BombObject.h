#pragma once

#include "MapObject/MovingMapObject.h"
#include "MapObject/Textures/BombObjectTexture.h"

class BombObject : public MovingMapObject
{
public:

    BombObject(const MapVector &pos,
               GameMap *map,
               BombHandler *bomb_handler);

    void update(const sf::Time &deltaTime) override;

    bool collideDD1(MovingMapObject *other_object) override;

    bool collideDD2(Character *other_object) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    BombObjectTexture m_texture;
    sf::Time m_time;
};