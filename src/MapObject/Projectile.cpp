#include "MapObject/Projectile.h"
#include "MapObject/Character.h"

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

void Projectile::update(const sf::Time &deltaTime)
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

bool Projectile::collideDD(Character *other_object)
{
    collideGeneric(other_object);
    addBomb({getPosition(),3*(int)getRadius(),0});
    other_object->damage(m_damage);
    kill();
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
