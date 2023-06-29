#include "resources_manager.h"
#include "Screen/HelpScreen.h"
#include "Button/TextureButton.h"
#include "Screen/MainScreen.h"

const sf::Vector2u HelpScreen::WINDOW_SIZE = sf::Vector2u(1200, 900);
const sf::Vector2f HelpScreen::BUTTONS_SIZE = sf::Vector2f(150, 50);

HelpScreen::HelpScreen() : m_helpTextIndex(0)
{

    m_buttonsGroup.add(std::make_unique<TextureButton>(
            sf::Vector2f((float) WINDOW_SIZE.x * 1 / 4 -
                         BUTTONS_SIZE.x / 2,
                         (float) WINDOW_SIZE.y * 0.75f -
                         BUTTONS_SIZE.y / 2),
            BUTTONS_SIZE,
            [this] { prevHelpText(); },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_LEFT_PATH)
    ));
    m_buttonsGroup.add(std::make_unique<TextureButton>(
            sf::Vector2f((float) WINDOW_SIZE.x * 2 / 4 -
                         BUTTONS_SIZE.x / 2,
                         (float) WINDOW_SIZE.y * 0.75f -
                         BUTTONS_SIZE.y / 2),
            BUTTONS_SIZE,
            [this] { exitToMainMenu(); },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_BACK_PATH)
    ));

    m_buttonsGroup.add(std::make_unique<TextureButton>(
            sf::Vector2f((float) WINDOW_SIZE.x * 3 / 4 -
                         BUTTONS_SIZE.x / 2,
                         (float) WINDOW_SIZE.y * 0.75f -
                         BUTTONS_SIZE.y / 2),
            BUTTONS_SIZE,
            [this] { nextHelpText(); },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_RIGHT_PATH)
    ));


    m_helpTextsHeader.emplace_back("OBJECTIVE:",
                                   resources_manager::get<sf::Font>(
                                           resources_manager::FONT_CALIBRI_PATH),
                                   50);
    m_helpText.emplace_back(
            "Your goal is to eliminate all the enemy potatoes and be the last team standing.\n"
            "Use a variety of weapons and tactics to strategically defeat your opponents.",
            resources_manager::get<sf::Font>(
                    resources_manager::FONT_CALIBRI_PATH),
            20);

    m_helpTextsHeader.emplace_back("GAMEPLAY:",
                                   resources_manager::get<sf::Font>(
                                           resources_manager::FONT_CALIBRI_PATH),
                                   50);
    m_helpText.emplace_back(
            "The game is turn-based.\n You control one Potato at a time, taking turns with the opposing team.\n"
            "Each Potato has a limited amount of health represented by a health bar.\nWhen the health reaches zero, the Potato is eliminated.\n"
            "Terrain and obstacles can affect the trajectory and outcome of your attacks, so plan your moves carefully.\n"
            "Collect crates that appear on the battlefield to gain advantages, such as extra weapons, health boosts.\n",
            resources_manager::get<sf::Font>(
                    resources_manager::FONT_CALIBRI_PATH),
            20);


    m_helpTextsHeader.emplace_back("WEAPONS:", resources_manager::get<sf::Font>(
            resources_manager::FONT_CALIBRI_PATH), 50);


    m_helpText.emplace_back("There are 5 weapons in the game:\n"
                            "1. Bazooka - a powerful weapon that can be used to inflict massive damage on the enemy.\n"
                            "2. Grenade - a weapon that can be used to inflict damage on the enemy.\n"
                            "3. Shotgun - a weapon that can be used to inflict damage on the enemy.\n"
                            "4. Cluster Bomb - a weapon that can be used to inflict damage on the enemy.\n"
                            "5. Homing Missile - a weapon that can be used to inflict damage on the enemy.\n",
                            resources_manager::get<sf::Font>(
                                    resources_manager::FONT_CALIBRI_PATH),
                            20);
    for (auto &header: m_helpTextsHeader)
    {
        header.setFillColor(sf::Color::Black);
        header.setOutlineColor(sf::Color::White);
        header.setPosition((float) WINDOW_SIZE.x / 2 -
                           header.getGlobalBounds().width / 2,

                           (float) WINDOW_SIZE.y * 0.05f);
    }
    for (auto &text: m_helpText)
    {
        text.setFillColor(sf::Color::Black);
        text.setOutlineColor(sf::Color::White);
        
        // header + line spacing (header line(50 px * 2))
        text.setPosition(50, (float) WINDOW_SIZE.y * 0.05f + 100); 
    }

}

std::unique_ptr<Screen> HelpScreen::run(sf::RenderWindow &window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y),
                  "Help Menu Screen",
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
        window.draw(m_helpTextsHeader[m_helpTextIndex]);
        window.draw(m_helpText[m_helpTextIndex]);
        window.display();
    }
    return std::move(m_nextScreen);
}

void HelpScreen::nextHelpText()
{
    m_helpTextIndex++;
    m_helpTextIndex %= (int) m_helpTextsHeader.size();
}

void HelpScreen::prevHelpText()
{
    m_helpTextIndex--;
    if (m_helpTextIndex < 0)
    {
        m_helpTextIndex = (int) m_helpTextsHeader.size() - 1;
    }
}

void HelpScreen::exitToMainMenu()
{
    m_nextScreen = std::make_unique<MainScreen>(getSettings());
}
