#include "ScreenManager.h"
#include "GameScreen.h"
#include <memory>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    ScreenManager screenManager(std::make_unique<GameScreen>());
    screenManager.run(window);
}