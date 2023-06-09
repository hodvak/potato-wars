#include <numbers>
#include "MapObject/Textures/RockTexture.h"
#include "resources_manager.h"
#include "MapObject/Rock.h"

RockTexture::RockTexture(const std::optional<PlayerColor> &color):
        m_color(color),
        m_life(3),
        m_rotation(0)
{

}

void RockTexture::setLife(int life)
{
    m_life = life;
}

void RockTexture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    const sf::Texture *texture = resources_manager::getTexture(
            "resources/Images/Textures/rocks.png");
    sf::Sprite sprite;
    sprite.setTexture(*texture);
    int left = 4;
    if (m_color)
    {
        left = (int) (*m_color);
    }
    int top = 3 - m_life;
    sprite.setTextureRect(sf::IntRect(left * 100, top * 100, 100, 100));
    sprite.setOrigin(50, 50);
    sprite.setScale(Rock::RADIUS / 50, Rock::RADIUS / 50);
    
    sprite.setPosition(0, 0);
    sprite.setRotation(m_rotation);
    
    target.draw(sprite, states);
}

void RockTexture::setAngle(float angle)
{
    m_rotation = angle * 180 / std::numbers::pi;
}


