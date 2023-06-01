#include "Screen/GameScreen.h"
#include "GameMap.h"
#include <memory>

static const float PI = acos(-1.0f);

GameScreen::GameScreen(const std::string &levelName) :
        m_game(levelName)
{

}

std::unique_ptr<Screen> GameScreen::run(sf::RenderWindow &window)
{
    window.create(sf::VideoMode(1080,720), "Game");
    window.setFramerateLimit(60);

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
                m_game.handleEvent(event);
            }

        }
        sf::Time delta = clock.restart();
        m_game.update(delta);
        // maybe for online game use this: 
        // m_game.update(sf::seconds(1.0f/60.0f));
        // all computers will end with the same result but the slower computers
        // will see the game slower (and update when they're done updating)
        
        window.clear();
        window.draw(m_game);
        window.display();
    }
    return nullptr;
}