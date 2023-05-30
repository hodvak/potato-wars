#include "MainScreen.h"
#include "ColorButton.h"
#include "GameScreen.h"
#include <iostream>

void nothing()
{}


MainScreen::MainScreen() :
        m_nextScreen(nullptr)
{
    // use std::bind to bind a function to a function object
    m_buttonsGroup.add(std::make_unique<ColorButton>(sf::Vector2f(100, 100),
                                                     sf::Vector2f(100, 100),
                                                     [this] { startGame(); },
                                                     sf::Color::Red,
                                                     "start"));
    m_buttonsGroup.add(std::make_unique<ColorButton>(sf::Vector2f(100, 300),
                                                     sf::Vector2f(100, 100),
                                                     nothing, sf::Color::Green,
                                                     "start2"));
    m_buttonsGroup.add(std::make_unique<ColorButton>(sf::Vector2f(100, 500),
                                                     sf::Vector2f(100, 100),
                                                     nothing, sf::Color::Blue,
                                                     "start3"));
    m_buttonsGroup.add(std::make_unique<ColorButton>(sf::Vector2f(100, 700),
                                                     sf::Vector2f(100, 100),
                                                     nothing,
                                                     sf::Color::Yellow,
                                                     "start4"));
}

std::unique_ptr<Screen> MainScreen::run(sf::RenderWindow &window)
{
    window.create(sf::VideoMode(1200, 900), "Main Menu Screen");
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
        window.draw(m_buttonsGroup);
        window.display();
    }
    return std::move(m_nextScreen);
}

void MainScreen::startGame()
{
    m_nextScreen = std::make_unique<GameScreen>();
}
