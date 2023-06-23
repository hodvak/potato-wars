#include "Weapon/Textures/GunTexture.h"
#include "resources_manager.h"
#include <numbers>

GunTexture::GunTexture(const sf::Vector2f &gunPosition,
                       float gunRadius,
                       const sf::Texture &gunTexture,
                       const sf::IntRect &textureRect,
                       const sf::Vector2f &aimPosition,
                       float aimRadius)
{
    m_gunSprite.setTexture(gunTexture);
    m_gunSprite.setTextureRect(textureRect);
    
    m_gunSprite.setOrigin(((float) textureRect.width / 2.0f),
                          ((float) textureRect.height / 2.0f));
    
    m_gunSprite.setScale(gunRadius / ((float) textureRect.height / 2.0f),
                         gunRadius / ((float) textureRect.height / 2.0f));

    

    m_gunSprite.setPosition(gunPosition);

    m_aimSprite.setTexture(resources_manager::get<sf::Texture>(
            resources_manager::IMG_AIM_PATH
    ));
    const sf::Vector2u &size = m_aimSprite.getTexture()->getSize();

    m_aimSprite.setScale(aimRadius / ((float) size.y / 2.0f),
                         aimRadius / ((float) size.y / 2.0f));

    m_aimSprite.setOrigin(((float) size.y / 2.0f),
                          ((float) size.y / 2.0f));

    m_aimSprite.setPosition(aimPosition);
}

void GunTexture::setPosition(const MapVector &position)
{
    m_gunSprite.setPosition(position);
    fixRotation();
}

void GunTexture::fixRotation()
{
    MapVector aimPosition = m_aimSprite.getPosition();
    MapVector gunPosition = m_gunSprite.getPosition();

    float rotation = (aimPosition - gunPosition).getAngle();
    
    // rotate the gun to the right direction
    if (rotation < -std::numbers::pi_v<float> / 2.0f || 
            rotation > std::numbers::pi_v<float> / 2.0f)
    {
        
        m_gunSprite.setScale(-std::abs(m_gunSprite.getScale().x),
                             m_gunSprite.getScale().y);
        rotation += std::numbers::pi_v<float>;
    }
    else
    {
        m_gunSprite.setScale(std::abs(m_gunSprite.getScale().x),
                             m_gunSprite.getScale().y);
    }
    
    m_gunSprite.setRotation(rotation * 180.0f / std::numbers::pi_v<float>);
}

void GunTexture::setAimPosition(const MapVector &aimPosition)
{
    m_aimSprite.setPosition(aimPosition);
    fixRotation();
}

void GunTexture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_gunSprite, states);
    target.draw(m_aimSprite, states);
}