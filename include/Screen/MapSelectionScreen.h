#pragma once
#include "resources_manager.h"
#include "Screen.h"
#include "Button/ButtonsGroup.h"
#include "level.h"

class MapSelectionScreen : public Screen
{
public:

    MapSelectionScreen();
    ~MapSelectionScreen() = default;
    std::unique_ptr<Screen> run(sf::RenderWindow &window) override;
    private:
    static const sf::Vector2u WINDOW_SIZE;
    void readLevels();
    std::vector<Level> m_levels;
    ButtonsGroup m_buttonsGroup;
    std::vector<std::unique_ptr<sf::RenderTexture>> m_buttonsTextures;
    std::unique_ptr<Screen> m_nextScreen;
    void makeButtons();
};
