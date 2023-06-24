#include <iostream>

#include "Screen/MainScreen.h"
#include "Button/TextureButton.h"
#include "Screen/GameScreen.h"
#include "resources_manager.h"
#include "Screen/HelpScreen.h"

const sf::Vector2u MainScreen::WINDOW_SIZE = sf::Vector2u(1200, 900);
const sf::Vector2f MainScreen::BUTTONS_SIZE = sf::Vector2f(150, 50);
const unsigned int MainScreen::NUM_OF_BUTTONS = 3;

MainScreen::MainScreen() :
        m_nextScreen(nullptr)
{
    m_buttonsGroup.add(std::make_unique<TextureButton>(
            sf::Vector2f((float) WINDOW_SIZE.x * 1 /
                         (float) (NUM_OF_BUTTONS + 1) -
                         (float) BUTTONS_SIZE.x / 2,
                         (float) WINDOW_SIZE.y * 0.75f -
                         (float) BUTTONS_SIZE.y / 2),
            MainScreen::BUTTONS_SIZE,
            [this] { startGame(); },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_NEW_GAME_PATH)
    ));

    m_buttonsGroup.add(std::make_unique<TextureButton>(
            sf::Vector2f((float) WINDOW_SIZE.x * 2 /
                         (float) (NUM_OF_BUTTONS + 1) -
                         (float) BUTTONS_SIZE.x / 2,
                         (float) WINDOW_SIZE.y * 0.75f -
                         (float) BUTTONS_SIZE.y / 2),
            BUTTONS_SIZE,
            [this] { help(); },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_HELP_PATH)
    ));

    m_buttonsGroup.add(std::make_unique<TextureButton>(
            sf::Vector2f((float) WINDOW_SIZE.x * 3 /
                         (float) (NUM_OF_BUTTONS + 1) -
                         (float) BUTTONS_SIZE.x / 2,
                         (float) WINDOW_SIZE.y * 0.75f -
                         (float) BUTTONS_SIZE.y / 2),
            BUTTONS_SIZE,
            [this] { std::cout << "todo: setting screen\n"; },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_SETTINGS_PATH)
    ));


}

std::unique_ptr<Screen> MainScreen::run(sf::RenderWindow &window)
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y),
                  "Potato War - Main Menu Screen",
                  sf::Style::Default,
                  settings);
    window.setFramerateLimit(60);
    
    sf::Sprite background;
    background.setTexture(
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BACKGROUND_MAIN_PATH
            )
    );
    background.scale(
            (float) WINDOW_SIZE.x /
            (float) background.getTexture()->getSize().x,
            (float) WINDOW_SIZE.y / (float) background.getTexture()->getSize().y
    );

    while (window.isOpen() && !m_nextScreen)
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    return nullptr;
                }

                case sf::Event::MouseButtonPressed:
                {
                    m_buttonsGroup.onClick(window.mapPixelToCoords(
                            sf::Vector2i(event.mouseButton.x,
                                         event.mouseButton.y)
                    ));
                    break;
                }

                case sf::Event::MouseMoved:
                {
                    m_buttonsGroup.onHover(window.mapPixelToCoords(
                            sf::Vector2i(event.mouseMove.x,
                                         event.mouseMove.y)
                    ));
                    break;
                }


                default:
                    break;

            }
        }

        window.clear();
        window.draw(background);
        window.draw(m_buttonsGroup);
        window.display();
    }
    return std::move(m_nextScreen);
}

void MainScreen::startGame()
{
    m_nextScreen = std::make_unique<GameScreen>(2);
}

void MainScreen::help()
{
    m_nextScreen = std::make_unique<HelpScreen>();
}

