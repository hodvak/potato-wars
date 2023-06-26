#pragma  once
#include "Screen.h"
#include "PlayerColor.h"
#include "Button/ButtonsGroup.h"
class EndGameScreen : public Screen
{
public:
    /**
     * constructor for the end game screen
     * @param winner the winner of the game
     */
    explicit EndGameScreen(PlayerColor winner);
    std::unique_ptr<Screen> run(sf::RenderWindow &window) override;

private:
    /**
     * the winner of the game
     */
    PlayerColor m_winner;
    static const sf::Vector2u WINDOW_SIZE;
    static const sf::Vector2f BUTTONS_SIZE;
    static const unsigned int NUM_OF_BUTTONS;
    ButtonsGroup m_buttonsGroup;
    std::unique_ptr<Screen> m_nextScreen;


};