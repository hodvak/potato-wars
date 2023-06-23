#include "MapObject/Textures/RockTexture.h"

#include <numbers>
#include "resources_manager.h"
#include "MapObject/Rock.h"

RockTexture::RockTexture(const std::optional<PlayerColor> &color) :
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
    const sf::Texture &texture = resources_manager::get<sf::Texture>(
            resources_manager::IMG_ROCK_PATH);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    unsigned int left = 4;
    if (m_color)
    {
        left = *m_color;
    }
    unsigned int top = 3 - m_life;

    sf::Vector2u size = resources_manager::IMG_ROCK_SIZE;
    
    // why can texture rect be negative? why int?
    sprite.setTextureRect(sf::IntRect((int)(left * size.x),
                                      (int)(top * size.y),
                                      (int)size.x,
                                      (int)size.y));

    sprite.setOrigin(((float)size.x)/2, ((float)size.y)/2);
    
    sprite.setScale(Rock::RADIUS / (((float)size.x)/2), 
                    Rock::RADIUS / (((float)size.y)/2));

    sprite.setPosition(0, 0);
    sprite.setRotation(m_rotation);

    target.draw(sprite, states);
}

void RockTexture::setAngle(float angle)
{
    m_rotation = angle * 180 / std::numbers::pi_v<float>;
}


