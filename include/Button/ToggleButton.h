#pragma once
#include "TextureButton.h"

class ToggleButton : public TextureButton
{
public:
    ToggleButton(const sf::Vector2f &pos,
                 const sf::Vector2f &size,
                 const std::function<void(bool )> &function,
                 const sf::Texture &texture,
                 const sf::Texture &texture2);



private:
    std::function<void(bool)> m_function;
    sf::Texture m_texture2;
    sf::Texture m_texture;
    bool m_clicked = false;
};