#include "Button/Button.h"

Button::Button(const sf::Vector2f &pos,
               const sf::Vector2f &size, 
               const std::function<void()> &function) :
        m_function(function),
        m_rect(pos, size)
{
    
}

void Button::onClick(const sf::Vector2f &pos)
{
    if (isContains(pos))
    {
        m_function();
    }
}

bool Button::isContains(const sf::Vector2f &pos)
{
    return m_rect.contains(pos);
}

sf::Vector2f Button::getPosition() const
{
    return {m_rect.left, m_rect.top};
}

sf::Vector2f Button::getSize() const
{
    return {m_rect.width, m_rect.height};
}
