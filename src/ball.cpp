#include "ball.h"
#include <iostream>
#include "Map.h"

Ball::Ball()
{
    m_shape.setRadius(10);
    m_shape.setFillColor(sf::Color::Yellow);
    m_shape.setPosition(floor(WIDTH/2), floor(HEIGHT/2));
}
Ball::Ball(sf::Vector2f pos)
{
    m_shape.setRadius(10);
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
void Ball::move(sf::Vector2i moveTo)
{
    m_shape.setPosition(moveTo.x, moveTo.y);
}

void Ball::setRadius(int radius)
{
    m_shape.setRadius(radius);

}

sf::Vector2f Ball::getPosition() const
{
    return m_shape.getPosition();
}
