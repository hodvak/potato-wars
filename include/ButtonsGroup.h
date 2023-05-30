#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include <vector>

class ButtonsGroup : public sf::Drawable
{
public:
    ButtonsGroup(
            std::vector<std::unique_ptr<Button>> buttons = std::vector<std::unique_ptr<Button>>()
    );

    void add(std::unique_ptr<Button> button);

    void onClick(sf::Vector2f pos);

    void onHover(sf::Vector2f pos);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    std::vector<std::unique_ptr<Button>> m_buttons;
};