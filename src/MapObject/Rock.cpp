#include "MapObject/Rock.h"
#include "MapObject/Character.h"
#include "MapObject/Projectile.h"

const float Rock::RADIUS = 7;
const float Rock::WEIGHT = 60;


bool Rock::collideDD2(Character *other_object)
{
    collideGeneric(other_object);
    if (!m_color ||  other_object->getColor() != *m_color)
    {
        other_object->damage(0.3);
        m_life--;
        if (m_life <= 0)
        {
            kill();
        }
        m_texture.setLife(m_life);
    }
    return true;
}

Rock::Rock(const MapVector &position, const MapVector &speed, GameMap *map,
           const std::optional<PlayerColor> &color) :
        MovingMapObject(Rock::WEIGHT,
                        position,
                        map,
                        Rock::RADIUS,
                        speed,
                        nullptr),
        m_life(3),
        m_color(color),
        m_texture(color)
{

}

void Rock::update(const sf::Time &deltaTime)
{
    MovingMapObject::update(deltaTime);
    m_texture.setAngle(getRotation());
    if(isRest())
    {
        kill();
    }
}

bool Rock::collideDD1(MovingMapObject *other_object)
{
    return other_object->collideDD2(this);
}

void Rock::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    target.draw(m_texture, states);
}
