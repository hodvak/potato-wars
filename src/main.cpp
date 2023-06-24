#include <memory>
#include <SFML/Graphics.hpp>
#include "Screen/ScreenManager.h"
#include "Screen/MainScreen.h"

int main()
{
    // make the window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Potato War!",sf::Style::Default,settings);
    
    // set the screen manager and run it
    ScreenManager screenManager(std::make_unique<MainScreen>());
    screenManager.run(window);
    
    // exit the program successfully
    return EXIT_SUCCESS;
}