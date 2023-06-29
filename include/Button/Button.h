#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "MapVector.h"

/**
 * abstract class for all buttons in the game
 * the button is a rectangle that can be clicked
 */
class Button : public sf::Drawable
{
public:
    /**
     * regular constructor
     * @param pos the position of the button
     * @param size the size of the button
     * @param function the function to call when the button is clicked
     */
    Button(const sf::Vector2f &pos,
           const sf::Vector2f &size,
           const std::function<void()> &function);

    /**
     * check if the button was clicked, and if so, call the function
     * @param pos the position of the click
     */
    virtual void onClick(const sf::Vector2f &pos);

    /**
     *  handle the hover event
     *  this function should be called every frame
     *  and check if the mouse is hovering over the button
     *  
     *  @param pos the position of the mouse
     */
    virtual void onHover(const sf::Vector2f &pos)
    {};
    [[nodiscard]] sf::Vector2f getPosition() const;
    [[nodiscard]] sf::Vector2f getSize() const;

    
    

protected:
    /**
     * check if a position is inside the button
     */
    bool isContains(const sf::Vector2f &pos);


private:
    /**
     * the function to call when the button is clicked
     */
    std::function<void()> m_function;

    /**
     * the rectangle of the button
     * this is used to check if the button was clicked
     */
    sf::FloatRect m_rect;
};