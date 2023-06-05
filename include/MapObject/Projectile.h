#pragma once
#include "MapObject/MovingMapObject.h"
class Projectile : public MovingMapObject
{
public:

    Projectile(float weight, 
               const MapVector &pos, 
               float radius, 
               float damage,
               const MapVector &start_velocity, 
               GameMap *map,
               BombHandler *bomb_handler);

    void update(const sf::Time &deltaTime) override;
    bool collide(MovingMapObject *other_object) override;
    bool collideDD(Character *other_object) override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    float m_damage;
};