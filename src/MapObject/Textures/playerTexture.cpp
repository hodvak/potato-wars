#include "MapObject/Textures/playerTexture.h"
#include "resources_manager.h"
#include "Const.h"

PlayerTexture::PlayerTexture(PlayerColor color, float radius) :
        m_angle(0),
        m_radius(radius)
{
    // todo: use consts for texture path?
    m_sprite.setTexture(*resources_manager::getTexture(
            "resources/Images/Textures/players.png"));
    m_sprite.setTextureRect(sf::IntRect(100 * (int) color, 0,
                                        100, 100));
    m_sprite.setScale(radius / 50, radius / 50);
    m_sprite.setOrigin(50, 50);

    m_lifeBar.setSize(sf::Vector2f(2 * radius, 5));
    m_lifeBar.setFillColor(getColor(color));
    m_lifeBar.setPosition(-radius, -2 * radius);

    m_fullLifeBar.setSize(sf::Vector2f(2 * radius, 5));
    m_fullLifeBar.setFillColor(sf::Color::Black);
    m_fullLifeBar.setPosition(-radius, -2 * radius);

}

void
PlayerTexture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_fullLifeBar, states);
    target.draw(m_lifeBar, states);

    // unclear why using degrees instead of radians here
    states.transform.rotate(m_angle);
    target.draw(m_sprite, states);
}

void PlayerTexture::setLife(float life)
{
    m_lifeBar.setSize(sf::Vector2f(2 * m_radius * life, 5));
}

void PlayerTexture::setAngle(float angle)
{
    // see `draw` function for why we use degrees instead of radians
    m_angle = angle * 180 / Consts::PI;
}
