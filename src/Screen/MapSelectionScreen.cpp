#include "Screen/MapSelectionScreen.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "GameMap.h"
#include "Button/TextureButton.h"
#include "Screen/GameScreen.h"
#include "Screen/MainScreen.h"
#include "Screen/ErrorScreen.h"

const sf::Vector2u MapSelectionScreen::WINDOW_SIZE = sf::Vector2u(1200, 900);
const sf::Vector2f MapSelectionScreen::BUTTON_SIZE = sf::Vector2f(200, 200);
const sf::Vector2u MapSelectionScreen::GRID_SIZE = sf::Vector2u(2, 2);

MapSelectionScreen::MapSelectionScreen(const Settings &settings):
        m_levels()
{
    setSettings(settings);
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
                return std::make_unique<MainScreen>(getSettings());
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                m_buttonsGroup.onClick(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
            }
            if (event.type == sf::Event::MouseMoved)
            {
                m_buttonsGroup.onHover(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
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
    file.open("resources/Levels/lvl_index.txt");
    if (!file.is_open())
    {
        m_nextScreen = std::make_unique<ErrorScreen>(
                "failed to open level_index.txt");
        return;
    }
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        int levelNumber;
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
    m_buttonsTextures.resize(m_levels.size());
    sf::RenderTexture renderTexture;
    for (unsigned i = 0; i < m_levels.size(); i++)
    {
        GameMap gameMap(m_levels[i]);
        sf::Vector2u mapSize = gameMap.getMask().getSize();

        renderTexture.create(mapSize.x, mapSize.y);
        
        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(gameMap);
        renderTexture.display();

        m_buttonsTextures[i] = renderTexture.getTexture();
        m_buttonsGroup.add(
                std::make_unique<TextureButton>(
                        sf::Vector2f(
                                ((float) (i % GRID_SIZE.x) + 0.5f) *
                                (float) WINDOW_SIZE.x /
                                (float) GRID_SIZE.x -
                                BUTTON_SIZE.x / 2,
                                ((float) (i / GRID_SIZE.x) + 0.5f) *
                                (float) WINDOW_SIZE.y /
                                (float) GRID_SIZE.y -
                                BUTTON_SIZE.y / 2
                        ),
                        BUTTON_SIZE,
                        [this, i]()
                        {
                            m_nextScreen = std::make_unique<GameScreen>(
                                    m_levels[i],getSettings());
                        },
                        m_buttonsTextures[i]
                ));
    }
}
