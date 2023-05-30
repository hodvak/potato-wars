#pragma once

#include "Button.h"
#include <optional>

class ColorButton : public Button
{
public:

    ColorButton(const sf::Vector2f &pos,
                const sf::Vector2f &size,
                const std::function<void()> &function,
                const sf::Color &colorRegular,
                const std::string &text,
                const std::optional<sf::Color> &colorHover = std::nullopt);

    void onHover(sf::Vector2f pos) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


private:
    bool m_isHover;
    sf::RectangleShape m_rect;
    sf::Color m_colorRegular;
    sf::Color m_colorHover;
    sf::Text m_text;
};