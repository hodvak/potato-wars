#include "MapObject/Projectile.h"
#include "MapObject/Character.h"

Projectile::Projectile(float weight,
                       const MapVector &pos,
                       float radius,
                       float damage,
                       const MapVector &startVelocity,
                       GameHelperData &gameHelperData):
    MovingMapObject(pos,
                    radius,
                    weight,
                    gameHelperData,
                    startVelocity),
    m_damage(damage)
{

}

void Projectile::update(const sf::Time &deltaTime)
{
    updatePosition(deltaTime);
    if(collisionMap())
    {
        kill();
        // todo: maybe change to a parameter instead of those magic numbers
        getGameHelperData().getBombHandler().addBomb({getPosition(),3*(int)getRadius(),100});
    }
}

bool Projectile::collideDD1(MovingMapObject &otherObject)
{
    return otherObject.collideDD2(*this);
}

bool Projectile::collideDD2(Character &otherObject)
{
    collideGeneric(otherObject);
    getGameHelperData().getBombHandler().addBomb({getPosition(),3*(int)getRadius(),0});
    otherObject.damage(m_damage);
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

bool Projectile::collideDD2(Projectile &otherObject)
{
    return true;
}
