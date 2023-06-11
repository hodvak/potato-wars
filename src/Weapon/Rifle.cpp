#include "Weapon/Rifle.h"
#include "MapObject/Projectile.h"

Rifle::Rifle(Character &character,
             const std::function<void(std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
             GameMap &map,
             BombHandler &bombHandler):
        Weapon(),
        m_character(character),
        m_aimPosition(0, 0),
        m_texture(character.getColor(),
                  character.getPosition(),
                  {0, 0},
                  character.getRadius()),
        m_addMapObjectFunc(addMapObjectFunc),
        m_map(map),
        m_bombHandler(bombHandler)
{

}

void Rifle::handleMouseMoved(const MapVector &mousePosition)
{
    m_aimPosition = mousePosition;
    m_texture.setAimPosition(mousePosition);
}

void Rifle::handleMousePressed(const MapVector &mousePosition)
{
    m_aimPosition = mousePosition;
    m_texture.setAimPosition(mousePosition);
    MapVector power = m_aimPosition - m_character.getPosition();
    MapVector startPosition = power;
    
    power.normalize(700);
    startPosition.normalize(m_character.getRadius()+6);
    startPosition = m_character.getPosition() + startPosition;
    
    m_addMapObjectFunc(std::make_unique<Projectile>(30,startPosition, 3, 0.6, power, &m_map, &m_bombHandler));
    die();
}

void Rifle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_texture, states);
}

void Rifle::update(const sf::Time &deltaTime)
{
    m_texture.setPosition(m_character.getPosition());
}
