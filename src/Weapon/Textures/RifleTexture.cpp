#include "Weapon/Textures/RifleTexture.h"
#include "resources_manager.h"
#include <numbers>

RifleTexture::RifleTexture(PlayerColor color,
                           MapVector position,
                           MapVector aimPosition,
                           float radius):
    m_color(color),
    m_position(position),
    m_aimPosition(aimPosition),
    m_radius(radius)
{
    
}

void RifleTexture::setPosition(MapVector position)
{
    m_position = position;
}

void RifleTexture::setAimPosition(MapVector aimPosition)
{
    m_aimPosition = aimPosition;
}

void RifleTexture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite aim;
    aim.setTexture(*resources_manager::getTexture("resources/Images/Textures/Aim.png"));
    aim.setOrigin(aim.getTexture()->getSize().x / 2, aim.getTexture()->getSize().y / 2);
    aim.setPosition(m_aimPosition);
    target.draw(aim, states);
    
    sf::Sprite sprite;
    sprite.setTexture(*resources_manager::getTexture("resources/Images/Textures/rifles.png"));
    int left = (int) (m_color);
    sprite.setTextureRect(sf::IntRect(left * 100, 0, 100, 100));
    sprite.setOrigin(50, 50);
    sprite.setScale(m_radius / 50, m_radius / 50);
    
    sprite.setPosition(m_position);
    sprite.setRotation((m_aimPosition - m_position).getAngle() * 180 / std::numbers::pi);
    
    target.draw(sprite, states);
    
}
