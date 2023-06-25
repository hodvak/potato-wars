
#include "Button/TextureButton.h"

TextureButton::TextureButton(const sf::Vector2f &pos,
                             const sf::Vector2f &size,
                             const std::function<void()> &function,
                             const sf::Texture &texture) :
        Button(pos, size, function),
        m_sprite(texture)
{
    m_sprite.setPosition(Button::getPosition());
    m_sprite.setScale(Button::getSize().x / (float) texture.getSize().x,
                      Button::getSize().y / (float) texture.getSize().y);

}

void TextureButton::onHover(const sf::Vector2f &pos)
{
    if (m_sprite.getGlobalBounds().contains(pos))
    {
        m_sprite.setColor(sf::Color(200, 200, 200, 255));
    }
    else
    {
        m_sprite.setColor(sf::Color(255, 255, 255, 255));
    }
}


void
TextureButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    target.draw(m_sprite, states);

}
