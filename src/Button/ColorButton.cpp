#include "Button/ColorButton.h"
#include "resources_manager.h"

ColorButton::ColorButton(const sf::Vector2f &pos,
                         const sf::Vector2f &size,
                         const std::function<void()> &function,
                         const sf::Color &colorRegular,
                         const std::string &text,
                         const std::optional<sf::Color> &colorHover)
        :
        Button(pos, size, function),
        m_isHover(false),
        m_colorRegular(colorRegular)
{
    // set the text
    m_text.setString(text);
    m_text.setPosition(pos);
    m_text.setFillColor(sf::Color::Black);
    m_text.setCharacterSize(20);
    m_text.setFont(*resources_manager::getFont("resources/Fonts/ARCADECLASSIC.TTF"));
    
    
    
    // if colorHover is not set, then set it to colorRegular with alpha 100/255
    // of the colorRegular alpha
    if (colorHover)
    {
        m_colorHover = *colorHover;
    }
    else
    {
        m_colorHover = m_colorRegular;
        m_colorHover.a = m_colorRegular.a * 100 / 255;
    }

    // set the rectangle shape
    m_rect.setFillColor(m_colorRegular);
    m_rect.setPosition(pos);
    m_rect.setSize(size);
}

void ColorButton::onHover(sf::Vector2f pos)
{
    // if the mouse is hovering over the button
    if (isContains(pos))
    {
        if (m_isHover)
        {
            // if the mouse is already hovering over the button, do nothing
            return;
        }
        // set the color to the hover color
        m_rect.setFillColor(m_colorHover);
        m_isHover = true;
    }
    else
    {
        if (!m_isHover)
        {
            // if the mouse is not hovering over the button, do nothing
            return;
        }
        // set the color to the regular color
        m_rect.setFillColor(m_colorRegular);
        m_isHover = false;
    }
}

void ColorButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // draw the rectangle
    target.draw(m_rect, states);
    // draw the text
    target.draw(m_text, states);
}
