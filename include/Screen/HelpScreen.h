#include "Screen.h"
#include "../Button/ButtonsGroup.h"

class HelpScreen : public Screen
{
    public:
    HelpScreen();
    std::unique_ptr<Screen> run(sf::RenderWindow &window) override;
private:
    ButtonsGroup m_buttonsGroup;
    std::unique_ptr<Screen> m_nextScreen;
    std::vector<sf::Text> m_helpText;
    std::vector<sf::Text> m_helpTextsHeader;
    void nextHelpText();
    void prevHelpText();
    int m_helpTextIndex;
};