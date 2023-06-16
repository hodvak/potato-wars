#include "MapObject/Rock.h"
#include "MapObject/Character.h"
#include "MapObject/Projectile.h"

const float Rock::RADIUS = 7;
const float Rock::WEIGHT = 60;


Rock::Rock(const MapVector &position,
           const MapVector &speed,
           const std::optional<PlayerColor> &color,
           const GameMap &map,
           BombHandler &bombHandler)
        :
        MovingMapObject(position,
                        Rock::RADIUS,
                        Rock::WEIGHT,
                        map,
                        bombHandler,
                        speed),
        m_life(3),
        m_color(color),
        m_texture(color)
{

}

void Rock::update(const sf::Time &deltaTime)
{
    MovingMapObject::update(deltaTime);
    m_texture.setAngle(getRotation());
    if (isRest())
    {
        kill();
    }
}

bool Rock::collideDD1(MovingMapObject &otherObject)
{
    return otherObject.collideDD2(*this);
}

bool Rock::collideDD2(Character &otherObject)
{
    collideGeneric(otherObject);
    if (!m_color || otherObject.getColor() != *m_color)
    {
        otherObject.damage(0.3);
        m_life--;
        if (m_life <= 0)
        {
            kill();
        }
        m_texture.setLife(m_life);
    }
    return true;
}

void Rock::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    target.draw(m_texture, states);
}
