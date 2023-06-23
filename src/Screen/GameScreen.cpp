#include "Screen/GameScreen.h"
#include "GameMap.h"
#include <memory>

GameScreen::GameScreen(const std::string &levelName) :
        m_game(levelName)
{

}

std::unique_ptr<Screen> GameScreen::run(sf::RenderWindow &window)
{
    window.create(sf::VideoMode(1080,720), "Game");
    window.setFramerateLimit(60);
    m_game.setTarget(&window);
    sf::Clock clock;
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else
            {
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    m_game.handleMousePressed(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
                }
                if(event.type == sf::Event::MouseWheelScrolled)
                {
                    m_game.handleScroll(event.mouseWheelScroll.delta);
                }
            }

        }
        sf::Time delta = clock.restart();
        m_game.update(delta);
        m_game.handleMouseMoved(window.mapPixelToCoords(sf::Mouse::getPosition(window)), window);
        // maybe for online game use this: 
        // m_game.update(sf::seconds(1.0f/60.0f));
        // all computers will end with the same result,
        // but the slower computers will see the game slower
        // (and update when they're done updating)
        
        window.clear();
        window.draw(m_game);
        window.display();
    }
    return nullptr;
}