#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

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
    Button(sf::Vector2f pos,
           sf::Vector2f size,
           std::function<void()> function);

    /**
     * check if the button was clicked, and if so, call the function
     * @param pos the position of the click
     */
    void onClick(sf::Vector2f pos);

    /**
     *  handle the hover event
     *  this function should be called every frame
     *  and check if the mouse is hovering over the button
     *  
     *  @param pos the position of the mouse
     */
    virtual void onHover(sf::Vector2f pos)
    {};
    
    

protected:
    /**
     * check if a position is inside the button
     */
    bool isContains(sf::Vector2f pos);


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