#include "Screen/EndGameScreen.h"
#include "Button/TextureButton.h"
#include "resources_manager.h"
#include "Screen/MapSelectionScreen.h"
#include "Screen/MainScreen.h"
#include "Physics.h"
#include "MapObject/MovingMapObject.h"
const sf::Vector2u EndGameScreen::WINDOW_SIZE = sf::Vector2u(1200, 900);
const sf::Vector2f EndGameScreen::BUTTONS_SIZE = sf::Vector2f(150, 50);
const unsigned int EndGameScreen::NUM_OF_BUTTONS = 3;
EndGameScreen::EndGameScreen(PlayerColor winner)
        : m_winner(winner), m_buttonsGroup(), m_nextScreen(nullptr)
{
    m_buttonsGroup.add(std::make_unique<TextureButton>(
            sf::Vector2f((float) WINDOW_SIZE.x * 1 /
                         (float) (NUM_OF_BUTTONS + 1) -
                         (float) BUTTONS_SIZE.x / 2,
                         (float) WINDOW_SIZE.y * 0.85f -
                         (float) BUTTONS_SIZE.y / 2),
            EndGameScreen::BUTTONS_SIZE,
            [this] { m_nextScreen = std::make_unique<MapSelectionScreen>(); },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_NEW_GAME_PATH)
    ));


    m_buttonsGroup.add(std::make_unique<TextureButton>(
            sf::Vector2f((float) WINDOW_SIZE.x * 3 /
                         (float) (NUM_OF_BUTTONS + 1) -
                         (float) BUTTONS_SIZE.x / 2,
                         (float) WINDOW_SIZE.y * 0.85f -
                         (float) BUTTONS_SIZE.y / 2),
            BUTTONS_SIZE,
            [this] { m_nextScreen = std::make_unique<MainScreen>(); },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_BACK_PATH)
    ));

}

std::unique_ptr<Screen> EndGameScreen::run(sf::RenderWindow &window)
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y),
                  "Potato War - End Game",
                  sf::Style::Default,
                  settings);
    window.setFramerateLimit(60);

    sf::Sprite background;
    background.setTexture(
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BACKGROUND_END_PATH
            )
    );
    background.scale(
            (float) WINDOW_SIZE.x /
            (float) background.getTexture()->getSize().x,
            (float) WINDOW_SIZE.y / (float) background.getTexture()->getSize().y
    );
    background.setColor(getColor(m_winner));
    //winnig text
    std::string winnigColor;
    switch (m_winner)
    {
        case PlayerColor::RED:
            winnigColor = "Red";
            break;
        case PlayerColor::BLUE:
            winnigColor = "Blue";
            break;
        case PlayerColor::GREEN:
            winnigColor = "Green";
            break;
        case PlayerColor::YELLOW:
            winnigColor = "Yellow";
            break;
        default:
            break;
    }
    sf::Text winningText;
    winningText.setFont(resources_manager::get<sf::Font>(
            resources_manager::FONT_ARCADE_PATH));
    winningText.setString(winnigColor +"  Team " +  " Won!");
    winningText.setCharacterSize(100);
    winningText.setFillColor(sf::Color::White);
    winningText.setOutlineColor(sf::Color::Black);
    winningText.setOutlineThickness(5);
    winningText.setPosition(
            (float) WINDOW_SIZE.x / 2 - winningText.getGlobalBounds().width / 2,
            (float) WINDOW_SIZE.y * 0.1f -
            winningText.getGlobalBounds().height / 2
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
        window.draw(winningText);
        window.display();
    }
    return std::move(m_nextScreen);
}


