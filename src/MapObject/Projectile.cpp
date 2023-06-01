#include "MapObject/Projectile.h"
#include "MapObject/Ball.h"

Projectile::Projectile(float weight,
                       const MapVector &pos,
                       float radius,
                       float damage,
                       const MapVector &start_velocity,
                       GameMap *map,
                       BombHandler *bomb_handler):
    MovingMapObject(weight, pos, map, radius, start_velocity, bomb_handler),
    m_damage(damage)
{

}

void Projectile::update(float deltaTime)
{
    updatePosition(deltaTime);
    if(collisionMap() != -1)
    {
        kill();
        addBomb({getPosition(),3*(int)getRadius(),100});
    }
}

bool Projectile::collide(MovingMapObject *other_object)
{
    return other_object->collideDD(this);
}

bool Projectile::collideDD(Ball *other_object)
{
    other_object->damage(m_damage);
    kill();
    collideGeneric(other_object);
    addBomb({getPosition(),3*(int)getRadius(),0});
    return true;
}

void Projectile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::CircleShape shape(getRadius());
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(getRadius(), getRadius());
    shape.setPosition(getPosition());
    target.draw(shape, states);
}
