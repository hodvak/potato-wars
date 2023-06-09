#include "Weapon/ThrowWeapon.h"
#include "MapObject/Character.h"

ThrowWeapon::ThrowWeapon(const Character &character,
                         MovingMapObject &weapon,
                         const std::function<void(MovingMapObject &)> &
                         addMapObjectFunc)
        :
        m_addMapObjectFunc(addMapObjectFunc),
        m_weapon(weapon),
        m_StartVelocity(1, 0),
        m_character(character),
        m_texture(character, {1,0}, m_maxDistance)
{
    fixPosition();
}


void ThrowWeapon::handleMouseMoved(const MapVector &mousePosition)
{
    m_StartVelocity = m_character.getPosition() - mousePosition;
    if(m_StartVelocity.getMagnitude() > m_maxDistance)
    {
        m_StartVelocity.normalize(m_maxDistance);
    }
    m_texture.setDirection(m_StartVelocity);
    fixPosition();
}

void ThrowWeapon::handleMousePressed(const MapVector &mousePosition)
{
    m_StartVelocity = m_character.getPosition() - mousePosition;
    if(m_StartVelocity.getMagnitude() > m_maxDistance)
    {
        m_StartVelocity.normalize(m_maxDistance);
    }
    m_texture.setDirection(m_StartVelocity);
    fixPosition();
    m_weapon.setVelocity(m_StartVelocity*3);
    m_addMapObjectFunc(m_weapon);
    die();
}

void ThrowWeapon::update(const sf::Time &deltaTime)
{
    fixPosition();
    m_texture.update(deltaTime);
}

void ThrowWeapon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_weapon, states);
    target.draw(m_texture, states);
}

void ThrowWeapon::fixPosition()
{
    MapVector startPosition = m_character.getPosition();
    MapVector diffPosition = m_StartVelocity;
    diffPosition.normalize(m_weapon.getRadius() + m_character.getRadius());
    startPosition += diffPosition;

    m_weapon.setPosition(startPosition);

}
