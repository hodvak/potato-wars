#pragma once

#include "Screen.h"

class GameScreen : public Screen
{
public:
    GameScreen();
    std::unique_ptr<Screen> run(sf::RenderWindow &window) override;
private:
    
};