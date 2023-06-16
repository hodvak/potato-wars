#include "MapObject/BombObject.h"

const float BombObject::RADIUS = 7;
const float BombObject::WEIGHT = 50;
const sf::Time BombObject::TIME_TO_EXPLODE = sf::seconds(10);
const Bomb BombObject::BOMB = Bomb({0, 0}, 50, 3000);

BombObject::BombObject(const MapVector &pos,
                       const GameMap &map,
                       BombHandler &bomb_handler) :
        MovingMapObject(
                pos,
                BombObject::RADIUS,
                BombObject::WEIGHT,
                map,
                bomb_handler
        ),

        m_texture(BombObject::RADIUS,
                  BombObject::TIME_TO_EXPLODE),

        m_time(sf::Time::Zero)
{

}

void BombObject::update(const sf::Time &deltaTime)
{
    MovingMapObject::update(deltaTime);
    m_time += deltaTime;
    m_texture.setRemainingTime(BombObject::TIME_TO_EXPLODE - m_time);
    if (m_time > BombObject::TIME_TO_EXPLODE)
    {
        Bomb bomb = BombObject::BOMB;
        bomb.pos = getPosition();
        addBomb(bomb);
        kill();
    }
    m_texture.setAngle(getRotation());
}

bool BombObject::collideDD1(MovingMapObject &other_object)
{
    return other_object.collideDD2(*this);
}

bool BombObject::collideDD2(Character &other_object)
{
    Bomb bomb = BombObject::BOMB;
    bomb.pos = getPosition();
    addBomb(bomb);
    kill();
    return true;
}

void BombObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    target.draw(m_texture, states);
}

