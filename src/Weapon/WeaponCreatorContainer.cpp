#include "Weapon/WeaponCreatorContainer.h"
#include "Weapon/Creators/WeaponCreator.h"
#include "resources_manager.h"

sf::Vector2u TABLE_SIZE(5, 3);

WeaponCreatorContainer::WeaponCreatorContainer(const MapVector &size,
                                               const MapVector &position) :
        m_size(size),
        m_position(position),
        m_weaponCreators()
{

}

void WeaponCreatorContainer::draw(sf::RenderTarget &target,
                                  sf::RenderStates states) const
{
    // full table
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(m_size.x, m_size.y));
    rectangle.setPosition(sf::Vector2f(m_position.x, m_position.y));
    rectangle.setFillColor(sf::Color(255, 255, 255, 100));
    target.draw(rectangle, states);


    // specific rectangles todo: add offset
    rectangle.setSize(
            sf::Vector2f(m_size.x / TABLE_SIZE.x, m_size.y / TABLE_SIZE.y));
    rectangle.setFillColor(sf::Color(255, 255, 255, 150));
    for (int i = 0; i < m_weaponCreators.size(); ++i)
    {
        rectangle.setPosition(
                sf::Vector2f(m_position.x + i * (m_size.x / TABLE_SIZE.x),
                             m_position.y));
        target.draw(rectangle, states);
        sf::Sprite sprite;
        sprite.setTexture(*m_weaponCreators[i]->getTexture());
        sprite.setTextureRect(m_weaponCreators[i]->getTextureRect());
        sprite.setPosition(
                sf::Vector2f(m_position.x + i * (m_size.x / TABLE_SIZE.x),
                             m_position.y));
        target.draw(sprite, states);
        sf::Text text;
        text.setFont(
                *resources_manager::getFont("resources/Fonts/ARCADE2.otf"));
        if (m_weaponCreators[i]->getAmount() == -1)
        {
            text.setString("inf");
        }
        else
        {
            text.setString(std::to_string(m_weaponCreators[i]->getAmount()));
        }
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(
                sf::Vector2f(m_position.x + i * (m_size.x / TABLE_SIZE.x),
                             m_position.y));
        target.draw(text, states);
    }
}

void WeaponCreatorContainer::addWeaponCreator(
        std::unique_ptr<WeaponCreator> &&weaponCreator)
{
    for (auto &creator : m_weaponCreators)
    {
        if (creator->getTexture() == weaponCreator->getTexture() &&
            creator->getTextureRect() == weaponCreator->getTextureRect())
        {
            creator->addAmount(weaponCreator->getAmount());
            return;
        }
    }
    m_weaponCreators.push_back(std::move(weaponCreator));
}

WeaponCreator *
WeaponCreatorContainer::getWeaponCreator(sf::Vector2f mousePosition)
{
    int index_x = (mousePosition.x - m_position.x) / (m_size.x / TABLE_SIZE.x);
    int index_y = (mousePosition.y - m_position.y) / (m_size.y / TABLE_SIZE.y);
    int index = index_x + index_y * TABLE_SIZE.x;

    if (index_x < 0 || index_x >= TABLE_SIZE.x ||
        index_y < 0 || index_y >= TABLE_SIZE.y)
    {
        return nullptr;
    }
    if (index >= m_weaponCreators.size())
    {
        return nullptr;
    }
    return m_weaponCreators[index].get();
}
