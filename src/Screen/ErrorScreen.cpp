#include "Screen/ErrorScreen.h"
#include "resources_manager.h"

ErrorScreen::ErrorScreen(const std::string &errorMessage):
    m_errorMessage(errorMessage)
{

}

ErrorScreen::ErrorScreen(std::string &&errorMessage):
    m_errorMessage(std::move(errorMessage))
{

}

std::unique_ptr<Screen> ErrorScreen::run(sf::RenderWindow &window)
{
    window.create(sf::VideoMode(500, 500), "Error");
    window.setFramerateLimit(60);
    sf::Text text;
    text.setFont(resources_manager::get<sf::Font>(resources_manager::FONT_CALIBRI_PATH));
    text.setCharacterSize(20);
    text.setString(m_errorMessage);
    
    text.setOrigin(
            text.getGlobalBounds().width / 2,
            text.getGlobalBounds().height / 2
    );
    
    text.setPosition(
            (float) window.getSize().x / 2,
            (float) window.getSize().y / 2
    );
    text.setFillColor(sf::Color::White);
    
    while(true)
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                return nullptr;
            }
        }
        window.clear();
        window.draw(text);
        window.display();
    }
}


