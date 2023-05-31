#pragma once
#include "Screen.h"
#include <memory>


/**
 * Class that manages the screens and runs them
 * the screens are run one after the other, until there is no next screen
 * (the next screen is nullptr)
 */
class ScreenManager
{
public:
    /**
     * constructor
     * @param screen the first screen to run
     */
    ScreenManager(std::unique_ptr<Screen> screen);
    
    /**
     * run the screens one after the other until there is no next screen
     * @param window the window to draw on
     */
    void run(sf::RenderWindow &window);

private:
    std::unique_ptr<Screen> m_currentScreen;
};