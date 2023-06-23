#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.h"

/**
 * a group of buttons
 * this class is used to draw and handle a group of buttons
 */
class ButtonsGroup : public sf::Drawable
{
public:
    /**
     * regular constructor
     * @param buttons the buttons to add to the group
     */
    explicit ButtonsGroup(
            std::vector<std::unique_ptr<Button>> &&buttons = std::vector<std::unique_ptr<Button>>()
    );

    /**
     * add a button to the group
     * @param button the button to add
     */
    void add(std::unique_ptr<Button> &&button);

    /**
     * check if a position is inside a button and if so, call the button's 
     * function that handles the click
     * @param pos the position of the click
     */
    void onClick(const sf::Vector2f &pos);

    /**
     * check if a position is inside a button and if so, call the button's 
     * function that handles the hover
     * @param pos the position of the mouse
     */
    void onHover(const sf::Vector2f &pos);

    /**
     * draw the buttons
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    size_t size() const;

    Button *operator [](int i) ;

private:
    
    /**
     * the buttons in the group
     * todo: maybe a unordered_map will be better, though we are not going to
     *       search for a button in the group, so it doesn't really matter 
     */
    std::vector<std::unique_ptr<Button>> m_buttons;
};