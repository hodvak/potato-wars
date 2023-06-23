#include "ParallaxLayer.h"
#include "MapVector.h"
ParallaxLayer::ParallaxLayer(const sf::Texture *texture,
                             const sf::Vector2f &size,
                             const sf::Vector2f &position,
                             float speed):
    m_sprite(*texture),
    m_size(size),
    m_position(position),
    m_speed(speed)
{
    m_sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
    m_sprite.setPosition(position.x/2, position.y/2);
    m_sprite.setScale(size.x / texture->getSize().x, size.y / texture->getSize().y);
}

void
ParallaxLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    target.draw(m_sprite, states);
}

void ParallaxLayer::update(const sf::Time &deltaTime)
{
    MapVector direction = (m_position - m_sprite.getPosition());
    if (direction.getMagnitude()>m_speed*deltaTime.asSeconds())
    {
        direction.normalize();
        m_sprite.move(direction*m_speed*deltaTime.asSeconds());
    }
    else
    {
        m_sprite.setPosition(m_position);
    }


}

void ParallaxLayer::setPosition(const sf::Vector2f &position)
{
    m_position = position;
}
