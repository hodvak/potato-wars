
#include "Button/ToggleButton.h"

ToggleButton::ToggleButton(const sf::Vector2f &pos, const sf::Vector2f &size,
                           const std::function<void(bool)> &function,
                           const sf::Texture &texture,
                           const sf::Texture &texture2):
                           m_function(function),
        TextureButton(pos, size, [&]{
            m_clicked = !m_clicked;

            if(m_clicked)
            {
                TextureButton::setTexture(m_texture2);
            }
            else
            {
                TextureButton::setTexture(m_texture);
            }

            m_function(m_clicked);
            }, texture),m_texture2(texture2),m_texture(texture),m_clicked(false)
{

}
