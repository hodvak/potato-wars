#include "Button/ButtonsGroup.h"

ButtonsGroup::ButtonsGroup(
        std::vector<std::unique_ptr<Button>> &&buttons) :
        m_buttons(std::move(buttons))
{

}

void ButtonsGroup::add(std::unique_ptr<Button> &&button)
{
    m_buttons.push_back(std::move(button));
}

void ButtonsGroup::onClick(const sf::Vector2f &pos)
{
    for (auto &button : m_buttons)
    {
        button->onClick(pos);
    }
}

void ButtonsGroup::onHover(const sf::Vector2f &pos)
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

size_t ButtonsGroup::size() const
{
    return m_buttons.size();
}

Button *ButtonsGroup::operator[](int i)
{
    return m_buttons[i].get();
}
