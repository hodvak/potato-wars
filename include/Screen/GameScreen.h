#pragma once

#include "Screen.h"
#include "Game.h"

class GameScreen : public Screen
{
public:
    explicit GameScreen(const std::string &levelName);
    std::unique_ptr<Screen> run(sf::RenderWindow &window) override;
private:
    Game m_game;
};