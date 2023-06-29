#pragma once

#include "resources_manager.h"
#include "Screen.h"
#include "Button/ButtonsGroup.h"
#include "level.h"

class MapSelectionScreen : public Screen
{
public:

    MapSelectionScreen(const Settings &settings);

    ~MapSelectionScreen() override = default;

    std::unique_ptr<Screen> run(sf::RenderWindow &window) override;

private:
    static const sf::Vector2u WINDOW_SIZE;
    static const sf::Vector2f BUTTON_SIZE;
    static const sf::Vector2u GRID_SIZE;

    void readLevels();

    std::vector<Level> m_levels;
    ButtonsGroup m_buttonsGroup;
    std::vector<sf::Texture> m_buttonsTextures;
    std::unique_ptr<Screen> m_nextScreen;

    void makeButtons();
};
