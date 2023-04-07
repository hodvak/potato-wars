#include <iostream>

#include "ball.h"
#include "Map.h"

Ball::Ball(sf::Vector2f pos, float radius)
{
    m_shape.setRadius(radius);
    m_shape.setFillColor(sf::Color::Yellow);
    m_shape.setOutlineColor(sf::Color::White);
    m_shape.setPosition(pos.x, pos.y);
    m_shape.setOrigin(m_shape.getRadius()/2, m_shape.getRadius()/2);
}
void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}
void Ball::update()
{

}

void Ball::setRadius(int radius)
{
    m_shape.setRadius(radius);

}

sf::Vector2f Ball::getPosition() const
{
    return m_shape.getPosition();
}
