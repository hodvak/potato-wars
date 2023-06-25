#pragma once

#include "Screen.h"
#include "Game.h"
#include "level.h"
/**
 * the main game screen, the game itself plays from here
 */
class GameScreen : public Screen
{
public:

    /**
     * constructor for the game screen with a level name to load
     * @param levelNumber the number of the level to load
     */
    explicit GameScreen(const Level &levelNumber);
    
    /**
     * the main loop of the game
     * @param window the window to draw on
     * @return nullptr for now
     * todo: add a return value for the next screen when there is one
     */
    std::unique_ptr<Screen> run(sf::RenderWindow &window) override;
private:
    /**
     * static consts data about the screen
     */
    static const sf::Vector2u WINDOW_SIZE;
    
    /**
     * the game itself
     */
    Game m_game;
};