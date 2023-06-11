#include "Weapon/ThrowWeapon.h"
#include "MapObject/Character.h"

ThrowWeapon::ThrowWeapon(const Character &character,
                         std::unique_ptr<MovingMapObject> &&weapon,
                         const std::function<void(std::unique_ptr<MovingMapObject> &&)> &
                         addMapObjectFunc)
        :
        m_addMapObjectFunc(addMapObjectFunc),
        m_weapon(std::move(weapon)),
        m_startVelocity(1, 0),
        m_character(character),
        m_texture(character, {1,0}, m_maxDistance)
{
    fixPosition();
}


void ThrowWeapon::handleMouseMoved(const MapVector &mousePosition)
{
    m_startVelocity = m_character.getPosition() - mousePosition;
    if(m_startVelocity.getMagnitude() > m_maxDistance)
    {
        m_startVelocity.normalize(m_maxDistance);
    }
    m_texture.setDirection(m_startVelocity);
    fixPosition();
}

void ThrowWeapon::handleMousePressed(const MapVector &mousePosition)
{
    m_startVelocity = m_character.getPosition() - mousePosition;
    if(m_startVelocity.getMagnitude() > m_maxDistance)
    {
        m_startVelocity.normalize(m_maxDistance);
    }
    m_texture.setDirection(m_startVelocity);
    fixPosition();
    m_weapon->setVelocity(m_startVelocity * 3);
    m_addMapObjectFunc(std::move(m_weapon));
    die();
}

void ThrowWeapon::update(const sf::Time &deltaTime)
{
    fixPosition();
    m_texture.update(deltaTime);
}

void ThrowWeapon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*m_weapon, states);
    target.draw(m_texture, states);
}

void ThrowWeapon::fixPosition()
{
    MapVector startPosition = m_character.getPosition();
    MapVector diffPosition = m_startVelocity;
    diffPosition.normalize(m_weapon->getRadius() + m_character.getRadius());
    startPosition += diffPosition;

    m_weapon->setPosition(startPosition);

}
