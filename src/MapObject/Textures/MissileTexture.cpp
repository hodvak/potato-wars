#include "MapObject/Textures/MissileTexture.h"
#include <numbers>

#include "resources_manager.h"

MissileTexture::MissileTexture(std::optional<PlayerColor> color, float angle, float radius) :
        m_color(color),
        m_angle(angle),
        m_time(sf::Time::Zero),
        m_radius(radius)
{

}

void MissileTexture::update(const sf::Time &deltaTime)
{
    m_time += deltaTime;
}

void MissileTexture::setAngle(float angle)
{
    m_angle = angle;
}

void
MissileTexture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite;
    sprite.setTexture(resources_manager::get<sf::Texture>(resources_manager::IMG_MISSILE_PATH));
    int x_index = PlayerColor::SIZE;
    if(m_color)
    {
        x_index = static_cast<int>(*m_color);
    }
    int y_index = (int)(
            m_time.asMicroseconds() / 
            TIME_FOR_ANIMATION.asMicroseconds()
            ) % resources_manager::IMG_MISSILE_ANIMATIONS;
    sprite.setTextureRect(sf::IntRect(x_index * resources_manager::IMG_MISSILE_SIZE.x,
                                      y_index * resources_manager::IMG_MISSILE_SIZE.y,
                                      resources_manager::IMG_MISSILE_SIZE.x,
                                      resources_manager::IMG_MISSILE_SIZE.y));
    sprite.setOrigin(resources_manager::IMG_MISSILE_ORIGIN);
    sprite.setScale(m_radius/resources_manager::IMG_MISSILE_RADIUS,
                    m_radius/resources_manager::IMG_MISSILE_RADIUS);
    
    sprite.setRotation(m_angle * 180 / std::numbers::pi_v<float>);
    sprite.setPosition(0, 0);
    target.draw(sprite, states);
}
