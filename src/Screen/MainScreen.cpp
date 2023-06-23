#include "Screen/MainScreen.h"
#include "Button/ColorButton.h"
#include "Button/TextureButton.h"
#include "Screen/GameScreen.h"
#include <iostream>
#include "resources_manager.h"
#include "Screen/HelpScreen.h"
void nothing()
{}



MainScreen::MainScreen() :
        m_nextScreen(nullptr)
{
    // use std::bind to bind a function to a function object
    float screen_width = 1200/6;
    float screen_height = 900;
    m_buttonsGroup.add(std::make_unique<TextureButton>(sf::Vector2f(screen_width*3-75, screen_height*0.75),
                                                       sf::Vector2f(150, 50),
                                                       [this] { startGame(); },
                                                       resources_manager::getTexture(
                                                               resources_manager::IMG_BUTTON_NEW_GAME_PATH)));
    m_buttonsGroup.add(std::make_unique<TextureButton>(sf::Vector2f(screen_width-75, screen_height*0.75),
                                                       sf::Vector2f(150, 50),
                                                       [this] { help(); },
                                                       resources_manager::getTexture(
                                                               resources_manager::IMG_BUTTON_HELP_PATH)));
    m_buttonsGroup.add(std::make_unique<TextureButton>(sf::Vector2f(screen_width*5-75, screen_height*0.75),
                                                       sf::Vector2f(150, 50),
                                                       [this] { startGame(); },
                                                       resources_manager::getTexture(
                                                               resources_manager::IMG_BUTTON_SETTINGS_PATH)));




}

std::unique_ptr<Screen> MainScreen::run(sf::RenderWindow &window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(1200, 900), "Main Menu Screen", sf::Style::Default, settings);
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
        sf::Sprite background;
        sf::Vector2f textureSize(
                resources_manager::getTexture(
                        resources_manager::IMG_BACKGROUND_MAIN_PATH)->getSize());
        background.setTexture(*resources_manager::getTexture(
                resources_manager::IMG_BACKGROUND_MAIN_PATH));
        background.scale(
                window.getSize().x / textureSize.x,
                window.getSize().y / textureSize.y
        );
        window.clear();
        window.draw(background);
        window.draw(m_buttonsGroup);
        window.display();
    }
    return std::move(m_nextScreen);
}

void MainScreen::startGame()
{
    m_nextScreen = std::make_unique<GameScreen>("lvl2");
}

void MainScreen::help()
{
    m_nextScreen = std::make_unique<HelpScreen>();
}

