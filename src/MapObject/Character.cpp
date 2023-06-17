#include <iostream>
#include "MapObject/Character.h"

const float Character::RADIUS = 10;
const float Character::WEIGHT = 200;

Character::Character(const MapVector &pos,
                     const GameMap &map,
                     BombHandler &bomb_handler,
                     const PlayerColor &color
) :
        MovingMapObject(pos,
                        Character::RADIUS,
                        Character::WEIGHT,
                        map,
                        bomb_handler
        ),
        m_life(1), // start with full life
        m_texture(color, Character::RADIUS),
        m_color(color),
        m_weaponCreatorContainer(
                sf::Vector2f((float) map.getMask().getSize().x / 2.0f,
                             (float) map.getMask().getSize().y / 2.0f),
                sf::Vector2f((float) map.getMask().getSize().x / 4.0f,
                             (float) map.getMask().getSize().y / 4.0f)
        )
{

}

void Character::update(const sf::Time &delta_time)
{
    MovingMapObject::update(delta_time);
    if (isRest())
    {
        setRotation(0);
    }
    m_texture.setAngle(getRotation());
}

bool Character::collideDD1(MovingMapObject &otherObject)
{
    return otherObject.collideDD2(*this);
}

bool Character::collideDD2(Character &otherObject)
{
    collideGeneric(otherObject);
    return true;
}

void Character::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    target.draw(m_texture, states);
}

void Character::damage(float damage)
{
    m_life -= damage;
    if (m_life <= 0)
    {
        kill();
    }
    m_texture.setLife(m_life);
}

PlayerColor Character::getColor() const
{
    return m_color;
}

const WeaponCreatorContainer &Character::getWeaponCreatorContainer() const
{
    return m_weaponCreatorContainer;
}

void Character::addWeaponCreator(std::unique_ptr<WeaponCreator> &&weaponCreator)
{
    m_weaponCreatorContainer.addWeaponCreator(std::move(weaponCreator));
}

WeaponCreatorContainer &Character::getWeaponCreatorContainer()
{
    return m_weaponCreatorContainer;
}

void Character::exploded(const Explosion &bomb)
{
    MovingMapObject::exploded(bomb);
    MapVector diff = getPosition() - bomb.pos;
    float distance = diff.getMagnitude();
    float bombDamage = bomb.force * (1 - distance / bomb.radius);
    if (bombDamage > 0)
    {
        damage(0.00002f * bombDamage);
    }
}

