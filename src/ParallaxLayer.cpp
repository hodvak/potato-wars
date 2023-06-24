#include "ParallaxLayer.h"
#include "MapVector.h"

ParallaxLayer::ParallaxLayer(const sf::Texture *texture,
                             const sf::Vector2f &size,
                             const sf::Vector2f &position,
                             float speed) :
        m_sprite(*texture),
        m_size(size),
        m_position(position.x / 2, position.y / 2),
        m_direction(m_position),
        m_speed(speed)
{
    m_sprite.setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
    m_sprite.setPosition(m_position);
    m_sprite.setScale(size.x / texture->getSize().x,
                      size.y / texture->getSize().y);
}

void
ParallaxLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    target.draw(m_sprite, states);
}

void ParallaxLayer::update(const sf::Time &deltaTime)
{

    MapVector delta = m_position - m_direction;
    m_sprite.setPosition(m_position.x+delta.x*m_speed,
                         m_position.y+delta.y*m_speed);
    std::cout<<m_position.x+delta.x*m_speed*deltaTime.asSeconds()<<std::endl;



}

void ParallaxLayer::setPosition(const sf::Vector2f &position)
{
    m_direction = position;
}
