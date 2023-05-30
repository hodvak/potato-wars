#include "ButtonsGroup.h"

ButtonsGroup::ButtonsGroup(
        std::vector<std::unique_ptr<Button>> buttons) :
        m_buttons(std::move(buttons))
{

}

void ButtonsGroup::add(std::unique_ptr<Button> button)
{
    m_buttons.push_back(std::move(button));
}

void ButtonsGroup::onClick(sf::Vector2f pos)
{
    for (auto &button : m_buttons)
    {
        button->onClick(pos);
    }
}

void ButtonsGroup::onHover(sf::Vector2f pos)
{
    for (auto &button : m_buttons)
    {
        button->onHover(pos);
    }
}

void ButtonsGroup::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (const auto &button : m_buttons)
    {
        target.draw(*button, states);
    }
}
