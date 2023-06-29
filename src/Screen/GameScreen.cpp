#include "Screen/GameScreen.h"
#include "GameMap.h"
#include <memory>
#include "resources_manager.h"
#include "Screen/EndGameScreen.h"
#include "Button/TextureButton.h"
#include "Button/ToggleButton.h"

const sf::Vector2u GameScreen::WINDOW_SIZE = {1080, 720};
static const int NUM_OF_BUTTONS = 3;
static const sf::Vector2f BUTTONS_SIZE = {150, 50};

GameScreen::GameScreen(const Level &level, const Settings &settings) :
        m_game(level)
{
    setSettings(settings);
    m_buttons.add(std::make_unique<TextureButton>(
            sf::Vector2f((float) WINDOW_SIZE.x * 1 /
                         (float) (NUM_OF_BUTTONS + 1) -
                         (float) BUTTONS_SIZE.x / 2,
                         (float) WINDOW_SIZE.y * 0.65f -
                         (float) BUTTONS_SIZE.y / 2),
            BUTTONS_SIZE,
            [this]
            {
                m_game.m_ChangeVolume(-10);
                setSettings(
                        {getSettings().m_mute, getSettings().m_volume - 10});
            },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_MINUS_PATH)
    ));

    m_buttons.add(std::make_unique<ToggleButton>(
            sf::Vector2f((float) WINDOW_SIZE.x * 2 /
                         (float) (NUM_OF_BUTTONS + 1) -
                         (float) BUTTONS_SIZE.x / 2,
                         (float) WINDOW_SIZE.y * 0.65f -
                         (float) BUTTONS_SIZE.y / 2),
            BUTTONS_SIZE,
            [this](bool b)
            {
                m_game.m_setMute(b);
                setSettings(
                        {b, getSettings().m_volume});
            },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_MUTE_PATH),
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_UNMUTE_PATH)
    ));

    m_buttons.add(std::make_unique<TextureButton>(
            sf::Vector2f((float) WINDOW_SIZE.x * 3 /
                         (float) (NUM_OF_BUTTONS + 1) -
                         (float) BUTTONS_SIZE.x / 2,
                         (float) WINDOW_SIZE.y * 0.65f -
                         (float) BUTTONS_SIZE.y / 2),
            BUTTONS_SIZE,
            [this]
            {
                setSettings(
                        {getSettings().m_mute, getSettings().m_volume + 10});
            },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_PLUS_PATH)
    ));

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
                if (event.type == sf::Event::MouseWheelScrolled)
                {

                    m_game.handleScroll(event.mouseWheelScroll.delta);
                }
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
                escapePressed(window);
            }

        }
        sf::Time delta = clock.restart();
        PlayerColor updateResult = m_game.update(
                delta);
        if (updateResult != PlayerColor::SIZE)
        {
            return std::make_unique<EndGameScreen>(updateResult, getSettings());
        }
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

void GameScreen::escapePressed(sf::RenderWindow &window)
{
    sf::RectangleShape background({static_cast<float>(WINDOW_SIZE.x * 0.75),
                                   static_cast<float>(WINDOW_SIZE.y * 0.75)});
    background.setFillColor({0, 0, 0, 100});
    background.setPosition({static_cast<float>(WINDOW_SIZE.x * 0.125),
                            static_cast<float>(WINDOW_SIZE.y * 0.125)});

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
                    m_buttons.onClick({(float) sf::Mouse::getPosition(window).x,
                                       (float) sf::Mouse::getPosition(
                                               window).y});
                }

            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
                return;
            }

        }
        window.clear();
        window.draw(m_game);
        sf::View view = window.getView();
        window.setView(window.getDefaultView());
        window.draw(background);
        window.draw(m_buttons);
        window.setView(view);
        window.display();
    }

}

