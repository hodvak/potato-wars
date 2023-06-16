#pragma once

#include "Screen.h"
#include "Button/ButtonsGroup.h"

/**
 * the main screen of the game
 * the screen that is shown when the game starts
 */
class MainScreen : public Screen
{
public:
    /**
     * regular constructor
     */
    MainScreen();
    
    /**
     * run the screen
     * @param window the window to draw on
     * @return the next screen, or nullptr if there is no next screen (on exit)
     */
    std::unique_ptr<Screen> run(sf::RenderWindow &window) override;

private:
    /**
     * start the game and set the next screen to the game screen
     */
    void startGame();
    
    /**
     * all the buttons (start game, exit, etc.)
     */
    ButtonsGroup m_buttonsGroup;
    
    /**
     * the next screen to run
     */
    std::unique_ptr<Screen> m_nextScreen;
};