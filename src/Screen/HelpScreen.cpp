#include "resources_manager.h"
#include "Screen/HelpScreen.h"
#include "Button/TextureButton.h"
#include "Screen/MainScreen.h"

HelpScreen::HelpScreen() : m_helpTextIndex(0)
{
    m_buttonsGroup.add(
            std::make_unique<TextureButton>(sf::Vector2f(200, 900 * 0.85),
                                            sf::Vector2f(150, 50),
                                            [this] { m_nextScreen = std::make_unique<MainScreen>(); },
                                            resources_manager::get<sf::Texture>(
                                                    resources_manager::IMG_BUTTON_BACK_PATH)));

    m_buttonsGroup.add(std::make_unique<TextureButton>(
            sf::Vector2f(1200 / 3 - 75, 900 * 0.85 - 100),
            sf::Vector2f(50, 50),
            [this] { prevHelpText(); },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_LEFT_PATH)));

    m_buttonsGroup.add(std::make_unique<TextureButton>(
            sf::Vector2f((1200 / 3) * 2 - 75, 900 * 0.85 - 100),
            sf::Vector2f(50, 50),
            [this] { nextHelpText(); },
            resources_manager::get<sf::Texture>(
                    resources_manager::IMG_BUTTON_RIGHT_PATH)));


    m_helpTextsHeader.emplace_back("OBJECTIVE:", *resources_manager::getFont(
            resources_manager::FONT_CALIBRI_PATH), 50);
    m_helpText.emplace_back("\n"
                            "Your goal is to eliminate all the enemy potatos and be the last team standing.\n"
                            "Use a variety of weapons and tactics to strategically defeat your opponents.",
                            *resources_manager::getFont(
                                    resources_manager::FONT_CALIBRI_PATH),
                            20);

    m_helpTextsHeader.emplace_back("GAMEPLAY:", *resources_manager::getFont(
            resources_manager::FONT_CALIBRI_PATH), 50);
    m_helpText.emplace_back("\n"
                            "The game is turn-based.\n You control one Potato at a time, taking turns with the opposing team.\n"
                            "Each Potato has a limited amount of health represented by a health bar.\nWhen the health reaches zero, the Potato is eliminated.\n"
                            "Terrain and obstacles can affect the trajectory and outcome of your attacks, so plan your moves carefully.\n"
                            "Collect crates that appear on the battlefield to gain advantages, such as extra weapons, health boosts.\n",
                            *resources_manager::getFont(
                                    resources_manager::FONT_CALIBRI_PATH),
                            20);


    m_helpTextsHeader.emplace_back("WEAPONS:", *resources_manager::getFont(
            resources_manager::FONT_CALIBRI_PATH), 50);


    m_helpText.emplace_back("There are 5 weapons in the game:\n"
                            "1. Bazooka - a powerful weapon that can be used to inflict massive damage on the enemy.\n"
                            "2. Grenade - a weapon that can be used to inflict damage on the enemy.\n"
                            "3. Shotgun - a weapon that can be used to inflict damage on the enemy.\n"
                            "4. Cluster Bomb - a weapon that can be used to inflict damage on the enemy.\n"
                            "5. Homing Missile - a weapon that can be used to inflict damage on the enemy.\n",
                            *resources_manager::getFont(
                                    resources_manager::FONT_CALIBRI_PATH),
                            20);
    for (auto &header: m_helpTextsHeader)
    {
        header.setFillColor(sf::Color::Black);
        header.setOutlineColor(sf::Color::White);
        header.setPosition(1200 / 2 - header.getGlobalBounds().width / 2,
                           900 * 0.05);
    }
    for (auto &text: m_helpText)
    {
        text.setFillColor(sf::Color::Black);
        text.setOutlineColor(sf::Color::White);
        text.setPosition(50, 900 * 0.15);
    }

}

std::unique_ptr<Screen> HelpScreen::run(sf::RenderWindow &window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(1200, 900), "Help Menu Screen",
                  sf::Style::Default, settings);
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
        window.draw(m_helpTextsHeader[m_helpTextIndex]);
        window.draw(m_helpText[m_helpTextIndex]);
        window.display();
    }
    return std::move(m_nextScreen);
}

void HelpScreen::nextHelpText()
{
    m_helpTextIndex++;
    m_helpTextIndex %= m_helpTextsHeader.size();
}

void HelpScreen::prevHelpText()
{
    m_helpTextIndex--;
    if (m_helpTextIndex < 0)
    {
        m_helpTextIndex = m_helpTextsHeader.size() - 1;
    }
}
