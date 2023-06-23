#include "Screen/ScreenManager.h"
#include "Screen/MainScreen.h"
#include "MapVector.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include <Physics.h>



int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!",sf::Style::Default,settings);
    ScreenManager screenManager(std::make_unique<MainScreen>());
    screenManager.run(window);
    return 0;
}