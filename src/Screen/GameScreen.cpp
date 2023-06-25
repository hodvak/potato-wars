#include "Screen/GameScreen.h"
#include "GameMap.h"
#include <memory>

const sf::Vector2u GameScreen::WINDOW_SIZE = {1080, 720};
GameScreen::GameScreen(const Level &levelNumber) :
        m_game(levelNumber)
{

}

std::unique_ptr<Screen> GameScreen::run(sf::RenderWindow &window)
{
    window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Potato War!");
    window.setFramerateLimit(60);
    m_game.setWindow(window);
    
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
                    m_game.handleMousePressed();
                }
                if(event.type == sf::Event::MouseWheelScrolled)
                {
                    // todo: is it really int? maybe float?
                    m_game.handleScroll((int)event.mouseWheelScroll.delta);
                }
            }

        }
        sf::Time delta = clock.restart();
        m_game.update(delta);
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