#include "Weapon/WeaponCreatorContainer.h"
#include "Weapon/Creators/WeaponCreator.h"
#include "resources_manager.h"

const sf::Vector2u WeaponCreatorContainer::TABLE_SIZE(5, 3);
const MapVector WeaponCreatorContainer::RECT_PERCENTAGE(0.8, 0.8);

WeaponCreatorContainer::WeaponCreatorContainer(GameHelperData &gameHelperData) :
        m_weaponCreators(),
        m_gameHelperData(gameHelperData)

{

}

void WeaponCreatorContainer::draw(sf::RenderTarget &target,
                                  sf::RenderStates states) const
{

    MapVector size = m_gameHelperData.getWindowSize() * RECT_PERCENTAGE;

    MapVector offset = m_gameHelperData.getWindowSize() *
                       ((MapVector(1, 1) - RECT_PERCENTAGE) / 2);
    // full table
    sf::View orgView = target.getView();
    target.setView(target.getDefaultView());


    sf::RectangleShape rectangle;
    rectangle.setSize(size);
    rectangle.setPosition(offset);
    rectangle.setFillColor(sf::Color(0, 0, 0, 100));
    target.draw(rectangle, states);


    rectangle.setSize(
            sf::Vector2f(size.x / TABLE_SIZE.x, size.y / TABLE_SIZE.y));

    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(sf::Color(0, 0, 0, 255));

    for (int i = 0; i < m_weaponCreators.size(); ++i)
    {
        rectangle.setPosition(
                sf::Vector2f(offset.x + (i % TABLE_SIZE.x) * (size.x / TABLE_SIZE.x),
                             offset.y + (i / TABLE_SIZE.x) * (size.y / TABLE_SIZE.y)));

        if (m_weaponCreators[i]->getAmount() != 0)
        {
            rectangle.setFillColor(sf::Color(0, 0, 0, 100));
        }
        else
        {
            rectangle.setFillColor(sf::Color(255, 0, 0, 100));
        }
        target.draw(rectangle, states);
        sf::Sprite sprite;
        sprite.setTexture(m_weaponCreators[i]->getTexture());
        sprite.setTextureRect(m_weaponCreators[i]->getTextureRect());
        sprite.setPosition(rectangle.getPosition());
        sprite.setScale(
                (size.x / TABLE_SIZE.x) / sprite.getGlobalBounds().width,
                (size.y / TABLE_SIZE.y) / sprite.getGlobalBounds().height);
        target.draw(sprite, states);
        sf::Text text;
        text.setFont(
                *resources_manager::getFont(resources_manager::FONT_ARCADE_PATH)
        );
        if (m_weaponCreators[i]->getAmount() == -1)
        {
            text.setString("inf");
        }
        else
        {
            text.setString(std::to_string(m_weaponCreators[i]->getAmount()));
        }
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(1);
        text.setPosition(rectangle.getPosition());
        target.draw(text, states);


    }
    target.setView(orgView);
}

void WeaponCreatorContainer::addWeaponCreator(
        std::unique_ptr<WeaponCreator> &&weaponCreator)
{

    for (auto &creator: m_weaponCreators)
    {
        if (&creator->getTexture() == &weaponCreator->getTexture() &&
            creator->getTextureRect() == weaponCreator->getTextureRect())
        {
            creator->addAmount(weaponCreator->getAmount());
            return;
        }
    }
    m_weaponCreators.push_back(std::move(weaponCreator));
}

WeaponCreator *
WeaponCreatorContainer::getWeaponCreator()
{
    MapVector size = m_gameHelperData.getWindowSize() * RECT_PERCENTAGE;

    MapVector offset = m_gameHelperData.getWindowSize() *
                       ((MapVector(1, 1) - RECT_PERCENTAGE) / 2);
    sf::Vector2f mousePosition = m_gameHelperData.getMousePositionInWindow();
    // not in the table
    if (mousePosition.x < offset.x ||
        mousePosition.x > offset.x + size.x ||
        mousePosition.y < offset.y ||
        mousePosition.y > offset.y + size.y)
    {
        return nullptr;
    }
    // calculate indexes
    int index_x = (mousePosition.x - offset.x) / (size.x / TABLE_SIZE.x);
    int index_y = (mousePosition.y - offset.y) / (size.y / TABLE_SIZE.y);
    int index = index_x + index_y * TABLE_SIZE.x;
    if (index >= m_weaponCreators.size())
    {
        return nullptr;
    }
    return m_weaponCreators[index].get();
}