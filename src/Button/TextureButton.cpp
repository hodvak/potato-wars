
#include "Button/TextureButton.h"

TextureButton::TextureButton(const sf::Vector2f &pos, const sf::Vector2f &size,
                             const std::function<void()> &function,
                             const sf::Texture *texture):
    Button(pos, size, function),
    m_texture(texture),
    m_sprite(*m_texture)
{
    m_sprite.setPosition(Button::getPosition());
    m_sprite.setScale(Button::getSize().x/texture->getSize().x, Button::getSize().y/texture->getSize().y);

}

void TextureButton::onHover(const sf::Vector2f &pos)
{
    if (m_sprite.getGlobalBounds().contains(pos))
    {
        m_sprite.setScale(Button::getSize().x/m_texture->getSize().x*1.2, Button::getSize().y/m_texture->getSize().y*1.2);
    }
    else
    {
        m_sprite.setScale(Button::getSize().x/m_texture->getSize().x, Button::getSize().y/m_texture->getSize().y);
    }

}


void TextureButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    target.draw(m_sprite, states);

}
