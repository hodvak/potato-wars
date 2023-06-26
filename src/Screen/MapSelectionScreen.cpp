#include "Screen/MapSelectionScreen.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "GameMap.h"
#include "Button/TextureButton.h"
#include "Screen/GameScreen.h"

const sf::Vector2u MapSelectionScreen::WINDOW_SIZE = sf::Vector2u(1200, 900);

MapSelectionScreen::MapSelectionScreen() :
        m_levels()
{
    readLevels();
    makeButtons();
}

std::unique_ptr<Screen> MapSelectionScreen::run(sf::RenderWindow &window)
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y),
                  "Potato War - Level Selection Screen",
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
            if (event.type == sf::Event::Closed ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                return nullptr;

            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                m_buttonsGroup.onClick(
                        sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            }
            if (event.type == sf::Event::MouseMoved)
            {
                m_buttonsGroup.onHover(
                        sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
            }
        }
        window.clear();
        window.draw(background);
        window.draw(m_buttonsGroup);


        window.display();
    }
    return std::move(m_nextScreen);
}

void MapSelectionScreen::readLevels()
{
    std::ifstream file;
    try
    {
        file.open("resources/Levels/lvl_index.txt");
    }
    catch (std::exception &e)
    {
        std::cerr << "failed to open level_index.txt" << std::endl;
        return;
    }
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string levelNumber;
        std::string groundTexture;
        std::string layersDir;
        int numberOfLayers;
        ss >> levelNumber >> groundTexture >> layersDir >> numberOfLayers;
        m_levels.push_back(
                {levelNumber, groundTexture, layersDir, numberOfLayers});
    }
}

void MapSelectionScreen::makeButtons()
{
    for (auto &level: m_levels)
    {
        GameMap gameMap(level);
        m_buttonsTextures.emplace_back(std::make_unique<sf::RenderTexture>());
        m_buttonsTextures.back()->create(gameMap.getMask().getSize().x,
                                         gameMap.getMask().getSize().y);
        //sf::RenderTexture renderTexture;
        gameMap.draw(*m_buttonsTextures.back(), sf::RenderStates::Default);
        // m_buttonsTextures.back()->update(renderTexture.getTexture());
        m_buttonsGroup.add(
                std::make_unique<TextureButton>(
                        sf::Vector2f{
                                (float )(std::stoi(level.levelNumber)-1)*400,
                                (float )WINDOW_SIZE.y / 2 - 100},
                        sf::Vector2f{300, -200},
                        [this, level]()
                        {
                            m_nextScreen = std::make_unique<GameScreen>(level);
                        },
                        m_buttonsTextures.back()->getTexture()
                ));
    }
}
