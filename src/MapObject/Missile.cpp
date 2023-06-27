#include "MapObject/Missile.h"

const float Missile::SPEED = 300.0f;
const float Missile::RADIUS = 7.0f;
const float Missile::MASS = 50.0f;
const Explosion Missile::EXPLOSION = {MapVector(0, 0), 100, 70000};

Missile::Missile(const MapVector &position,
                 GameHelperData &data,
                 float angle,
                 PlayerColor color):
        MovingMapObject(position, RADIUS, MASS, data, MapVector::getVectorFromAngle(angle, SPEED)),
        m_texture(color, angle, RADIUS)
{
    
}

void Missile::update(const sf::Time &deltaTime)
{
    MovingMapObject::updatePosition(deltaTime);
    m_texture.update(deltaTime);
    std::optional angle = MovingMapObject::collisionMap();
    if(angle)
    {
        Explosion explosion = EXPLOSION;
        explosion.pos = getPosition();
        getGameHelperData().getBombHandler().addBomb(explosion);
        kill();
    }
}

bool Missile::collideDD1(MovingMapObject &otherObject)
{
    return otherObject.collideDD2(*this);
}

bool Missile::collideDD2(Character &otherObject)
{
    Explosion explosion = EXPLOSION;
    explosion.pos = getPosition();
    getGameHelperData().getBombHandler().addBomb(explosion);
    kill();
    return true;
}

void Missile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    target.draw(m_texture, states);
}
