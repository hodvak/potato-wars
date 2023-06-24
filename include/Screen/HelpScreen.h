#include "Screen.h"
#include "Button/ButtonsGroup.h"

// todo: think about `on exit go to main menu screen or exit?`
//       for now its `exit`

/**
 * the help screen of the game
 * the screen that is shown when the user clicks on the help button
 */
class HelpScreen : public Screen
{
    public:
    /**
     * regular constructor
     */
    HelpScreen();
    
    /**
     * run the screen
     * @param window the window to draw on
     * @return the next screen (may only be the main menu screen)
     *         or nullptr if there is no next screen (on exit)
     */
    std::unique_ptr<Screen> run(sf::RenderWindow &window) override;
    
private:
    /**
     * static consts data about the screen
     */
    static const sf::Vector2u WINDOW_SIZE;
    static const sf::Vector2f BUTTONS_SIZE;
    
    /**
     * the buttons (next, prev, exit(to main menu)))
     */
    ButtonsGroup m_buttonsGroup;
    
    /**
     * the next screen to run (may only be the main menu screen or nullptr)
     */
    std::unique_ptr<Screen> m_nextScreen;
    
    /**
     * the help text
     */
    std::vector<sf::Text> m_helpText;
    std::vector<sf::Text> m_helpTextsHeader;
    
    /**
     * buttons functions
     * get the next/prev help text
     * and exit to main menu
     */
    void nextHelpText();
    void prevHelpText();
    void exitToMainMenu();
    
    /**
     * the index of the current help text
     */
    int m_helpTextIndex;
};