#include <format>
#include <numbers>
#include "MapObject/Textures/BombObjectTexture.h"
#include "resources_manager.h"

BombObjectTexture::BombObjectTexture(float radius, const sf::Time &time) :
        m_radius(radius),
        m_angle(0.0f),
        m_remainedTime(time)
{

}

void
BombObjectTexture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Text timeText;
    timeText.setFont(
            resources_manager::get<sf::Font>(resources_manager::FONT_ARCADE_PATH)
    );

    timeText.setCharacterSize(20);
    timeText.setString(std::format("{:.2f}", m_remainedTime.asSeconds()));
    timeText.setPosition(-timeText.getLocalBounds().width / 2,
                         -timeText.getLocalBounds().height - 2 * m_radius - 2);

    target.draw(timeText, states);

    const sf::Texture &texture = resources_manager::get<sf::Texture>
            (
                    resources_manager::IMG_BOMB_PATH
            );
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin((float)texture.getSize().x / 2.0f, 
                     (float)texture.getSize().y / 2.0f);

    sprite.setScale(m_radius / ((float)texture.getSize().x / 2.0f),
                    m_radius / ((float)texture.getSize().y / 2.0f));

    states.transform.rotate(m_angle);
    target.draw(sprite, states);
}

void BombObjectTexture::setRemainingTime(const sf::Time &time)
{
    m_remainedTime = time;
}

void BombObjectTexture::setAngle(float angle)
{
    m_angle = angle * 180 / std::numbers::pi_v<float>;
}

