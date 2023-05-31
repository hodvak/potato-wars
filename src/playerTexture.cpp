#include "playerTexture.h"
#include "resources_manager.h"

PlayerTexture::PlayerTexture(PlayerColor color, float radius):
    m_angle(0),
    m_radius(radius)
{
    m_sprite.setTexture(*resources_manager::getTexture("resources/players.png"));
    m_sprite.setTextureRect(sf::IntRect(100*(int)color, 0, 
                                        100, 100));
    m_sprite.setScale(radius/50, radius/50);
    m_sprite.setOrigin(50, 50);
    
    m_lifeBar.setSize(sf::Vector2f(2 * radius, 5));
    m_lifeBar.setFillColor(sf::Color::Red);
    m_lifeBar.setPosition(-radius, -2*radius);
    
    m_fullLifeBar.setSize(sf::Vector2f(2*radius, 5));
    m_fullLifeBar.setFillColor(sf::Color::Black);
    m_fullLifeBar.setPosition(-radius, -2*radius);

}

void PlayerTexture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_fullLifeBar,states);
    target.draw(m_lifeBar, states);
    states.transform.rotate(m_angle);
    target.draw(m_sprite, states);
}

void PlayerTexture::setLife(float life)
{
    m_lifeBar.setSize(sf::Vector2f(2 * m_radius * life, 5));
}

void PlayerTexture::setAngle(float angle)
{
    m_angle = angle;
}
