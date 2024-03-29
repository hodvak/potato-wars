#include "Weapon/ThrowWeapon.h"
#include "MapObject/Character.h"
#include "resources_manager.h"
ThrowWeapon::ThrowWeapon(const Character &character,
                         std::unique_ptr<MovingMapObject> &&weapon,
                         GameHelperData &gameHelperData)
        : 
        Weapon(gameHelperData),
        m_weapon(std::move(weapon)),
        m_startVelocity(1, 0),
        m_character(character),
        m_texture(character, 
                  {1,0},
                  *m_weapon,
                  MAX_MOUSE_DISTANCE)
{
    //fixPosition();
}


void ThrowWeapon::handleMouseMoved(const MapVector &mousePosition)
{
    m_startVelocity = m_character.getPosition() - mousePosition;
    if(m_startVelocity.getMagnitude() > MAX_MOUSE_DISTANCE)
    {
        m_startVelocity.normalize(MAX_MOUSE_DISTANCE);
    }
    m_texture.setDirection(m_startVelocity);
//    fixPosition();
}

void ThrowWeapon::handleMousePressed(const MapVector &mousePosition)
{
    m_startVelocity = m_character.getPosition() - mousePosition;
    if(m_startVelocity.getMagnitude() > MAX_MOUSE_DISTANCE)
    {
        m_startVelocity.normalize(MAX_MOUSE_DISTANCE);
    }
    m_texture.setDirection(m_startVelocity);
    fixPosition();
    m_weapon->setVelocity(m_startVelocity * 3);
    getGameHelperData().addMapObject(std::move(m_weapon));
    getGameHelperData().addSound(resources_manager::SOUND_WEAPONTHROW_PATH);
    die();
}

void ThrowWeapon::update(const sf::Time &deltaTime)
{
//    fixPosition();
    m_texture.update(deltaTime);
}

void ThrowWeapon::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    m_texture.draw(target, states);
//    m_weapon->draw(target, states);
}

void ThrowWeapon::fixPosition()
{
    MapVector startPosition = m_character.getPosition();
    MapVector diffPosition = m_startVelocity;
    diffPosition.normalize(m_weapon->getRadius() + m_character.getRadius());
    startPosition += diffPosition;

    m_weapon->setPosition(startPosition);

}

void ThrowWeapon::setDirectionTexture(MapVector direction)
{
    m_texture.setDirection(direction);
}
