#include <numbers>
#include "MapObject/Textures/playerTexture.h"
#include "resources_manager.h"

PlayerTexture::PlayerTexture(PlayerColor color, float radius) :
        m_angle(0),
        m_radius(radius)
{
    m_sprite.setTexture(resources_manager::get<sf::Texture>(
                                resources_manager::IMG_PLAYER_PATH
                        )
    );
    const sf::Vector2u &size = resources_manager::IMG_PLAYER_SIZE;

    m_sprite.setTextureRect(sf::IntRect((int) size.x * (int) color,
                                        0,
                                        (int) size.x,
                                        (int) size.y));

    m_sprite.setScale(radius / ((float) size.y / 2.0f),
                      radius / ((float) size.y / 2.0f));

    m_sprite.setOrigin(((float) size.y / 2.0f),
                       ((float) size.y / 2.0f));

    m_lifeBar.setSize(sf::Vector2f(2 * radius, radius / 3));
    m_shieldBar.setSize(sf::Vector2f(0, radius / 3));
    m_lifeBar.setFillColor(getColor(color));
    m_shieldBar.setFillColor(sf::Color::Cyan);
    m_lifeBar.setPosition(-radius, -2 * radius);
    m_shieldBar.setPosition(-radius, -2 * radius- m_lifeBar.getSize().y);
    m_fullLifeBar.setSize(sf::Vector2f(2 * radius, radius / 3));
    m_fullLifeBar.setFillColor(sf::Color::Black);
    m_fullLifeBar.setPosition(-radius, -2 * radius);

}

void
PlayerTexture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_fullLifeBar, states);
    target.draw(m_lifeBar, states);
    target.draw(m_shieldBar, states);
    // unclear why using degrees instead of radians here
    states.transform.rotate(m_angle);
    target.draw(m_sprite, states);
}

void PlayerTexture::setLife(float life)
{
    if (life < 0)
    {
        life = 0;
    }
    if (life > 2)
    {
        life = 2;
    }
    if(life > 1)
    {
        m_shieldBar.setSize(sf::Vector2f(2 * m_radius * (life - 1), m_radius / 3));
        life = 1;
    }
    else
    {
        m_shieldBar.setSize(sf::Vector2f(0, m_radius / 3));
    }

    m_lifeBar.setSize(sf::Vector2f(2 * m_radius * life, m_radius / 3));
}

void PlayerTexture::setAngle(float angle)
{
    // see `draw` function for why we use degrees instead of radians
    m_angle = angle * 180 / std::numbers::pi_v<float>;
}
