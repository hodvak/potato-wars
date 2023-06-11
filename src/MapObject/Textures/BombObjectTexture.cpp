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
            *resources_manager::getFont("resources/Fonts/ARCADE2-Regular.otf"));
    timeText.setCharacterSize(20);
    timeText.setString(std::format("{:.2f}", m_remainedTime.asSeconds()));
    timeText.setPosition(-timeText.getLocalBounds().width / 2,
                         -timeText.getLocalBounds().height - 2 * m_radius - 2);
    
    target.draw(timeText, states);
    
    const sf::Texture *texture = resources_manager::getTexture(
            "resources/Images/Textures/bomb.png");
    sf::Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
    sprite.setOrigin(50, 50);
    sprite.setScale(m_radius / 50, m_radius / 50);

    states.transform.rotate(m_angle);
    target.draw(sprite, states);
}

void BombObjectTexture::setReminingTime(const sf::Time &time)
{
    m_remainedTime = time;
}

void BombObjectTexture::setAngle(float angle)
{
    m_angle = angle * 180 / std::numbers::pi_v<float>;
}

