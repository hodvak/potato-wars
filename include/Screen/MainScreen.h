#pragma once

#include "Screen.h"
#include "Button/ButtonsGroup.h"

class MainScreen : public Screen
{
public:
    MainScreen();
    std::unique_ptr<Screen> run(sf::RenderWindow &window) override;

private:
    void startGame();
    ButtonsGroup m_buttonsGroup;
    std::unique_ptr<Screen> m_nextScreen;
};