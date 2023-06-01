#include "Button/Button.h"

Button::Button(sf::Vector2f pos, 
               sf::Vector2f size, 
               const std::function<void()> &function) :
        m_function(function),
        m_rect(pos, size)
{
    
}

void Button::onClick(sf::Vector2f pos)
{
    if (isContains(pos))
    {
        m_function();
    }
}

bool Button::isContains(sf::Vector2f pos)
{
    return m_rect.contains(pos);
}
