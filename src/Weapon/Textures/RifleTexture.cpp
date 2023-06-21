#include "Weapon/Textures/RifleTexture.h"
#include "resources_manager.h"
#include <numbers>

RifleTexture::RifleTexture(PlayerColor color,
                           const MapVector &position,
                           const MapVector &aimPosition,
                           float radius) :
        m_color(color),
        m_position(position),
        m_aimPosition(aimPosition),
        m_radius(radius * 1.5f)
// todo: is 1.5f a magic number?
//       the size of the rifle is a ratio of the radius
//       add to consts of the object maybe?
{

}

void RifleTexture::setPosition(const MapVector &position)
{
    m_position = position;
}

void RifleTexture::setAimPosition(const MapVector &aimPosition)
{
    m_aimPosition = aimPosition;
}

void RifleTexture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite aim;
    aim.setTexture(*resources_manager::getTexture(
            resources_manager::IMG_AIM_PATH));
    aim.setOrigin(aim.getTexture()->getSize().x / 2,
                  aim.getTexture()->getSize().y / 2);
    aim.setPosition(m_aimPosition);
    target.draw(aim, states);

    sf::Sprite sprite;
    sprite.setTexture(*resources_manager::getTexture(
            resources_manager::IMG_RIFLE_PATH));
    int left = (int) (m_color);
    sprite.setTextureRect(sf::IntRect(
            left * (int) resources_manager::IMG_RIFLE_SIZE.x,
            0,
            (int) resources_manager::IMG_RIFLE_SIZE.x,
            (int) resources_manager::IMG_RIFLE_SIZE.y
    ));

    sprite.setOrigin(
            (float) resources_manager::IMG_RIFLE_SIZE.x / 2.0f,
            (float) resources_manager::IMG_RIFLE_SIZE.y / 2.0f
    );
    sprite.setScale(
            m_radius / ((float) resources_manager::IMG_RIFLE_SIZE.x / 2.0f),
            m_radius / ((float) resources_manager::IMG_RIFLE_SIZE.x / 2.0f)
    );
    
    sprite.setPosition(m_position);
    float angle = (m_aimPosition - m_position).getAngle();
    sprite.setRotation(angle * 180 / std::numbers::pi_v<float>);

    if (angle > std::numbers::pi_v<float> / 2 ||
        angle < -std::numbers::pi_v<float> / 2)
    {
        sprite.scale(1, -1);
    }

    target.draw(sprite, states);

}
