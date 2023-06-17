#include "MapObject/Bomb.h"

const float Bomb::RADIUS = 7;
const float Bomb::WEIGHT = 50;
const sf::Time Bomb::TIME_TO_EXPLODE = sf::seconds(10);
const Explosion Bomb::BOMB = Explosion({0, 0}, 50, 3000);

Bomb::Bomb(const MapVector &pos,
           const GameMap &map,
           BombHandler &bomb_handler) :
        MovingMapObject(
                pos,
                Bomb::RADIUS,
                Bomb::WEIGHT,
                map,
                bomb_handler
        ),

        m_texture(Bomb::RADIUS,
                  Bomb::TIME_TO_EXPLODE),

        m_time(sf::Time::Zero)
{

}

void Bomb::update(const sf::Time &deltaTime)
{
    MovingMapObject::update(deltaTime);
    m_time += deltaTime;
    m_texture.setRemainingTime(Bomb::TIME_TO_EXPLODE - m_time);
    if (m_time > Bomb::TIME_TO_EXPLODE)
    {
        Explosion bomb = Bomb::BOMB;
        bomb.pos = getPosition();
        addBomb(bomb);
        kill();
    }
    m_texture.setAngle(getRotation());
}

bool Bomb::collideDD1(MovingMapObject &other_object)
{
    return other_object.collideDD2(*this);
}

bool Bomb::collideDD2(Character &other_object)
{
    Explosion bomb = Bomb::BOMB;
    bomb.pos = getPosition();
    addBomb(bomb);
    kill();
    return true;
}

void Bomb::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    target.draw(m_texture, states);
}

