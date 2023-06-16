#pragma once

#include <optional>
#include "Button.h"

/**
 * a button with a color (rectangle with text on it)
 */
class ColorButton : public Button
{
public:

    /**
     * regular constructor
     * @param pos the position of the button
     * @param size the size of the button
     * @param function the function to call when the button is clicked
     * @param colorRegular the color of the button when it's not hovered
     * @param text the text on the button
     * @param colorHover the color of the button when it's hovered
     */
    ColorButton(const sf::Vector2f &pos,
                const sf::Vector2f &size,
                const std::function<void()> &function,
                const sf::Color &colorRegular,
                const std::string &text,
                const std::optional<sf::Color> &colorHover = std::nullopt);

    /**
     * change the color of the button if the position is inside the button
     * @param pos the position of the mouse
     */
    void onHover(const sf::Vector2f &pos) override;

    /**
     * draw the button
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


private:
    bool m_isHover;
    sf::RectangleShape m_rect;
    sf::Color m_colorRegular;
    sf::Color m_colorHover;
    sf::Text m_text;
};