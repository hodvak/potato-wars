#include "Team.h"

Team::Team(const PlayerColor &color) :
        m_currentCharacter(nullptr),
        m_weapon(nullptr),
        m_color(color),
        m_mousePosition(0, 0)
{

}


void Team::removeDeadCharacters()
{
    std::erase_if(m_characters, [](Character *character)
    {
        return !character->isAlive();
    });
}

void Team::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::CircleShape shape(10);
    shape.setOrigin(10, 10);
    sf::Color color = ::getColor(m_color);
    color.a = 100;
    sf::RenderStates weaponStates = states;
    sf::Vector2<float> newC = (target.getView().getCenter() - target.getView().getSize()) / 2.f;


    weaponStates.transform.translate(newC);


    shape.setFillColor(color);
    if (m_weapon)
    {
        target.draw(*m_weapon, states);
    }
    else if (m_currentCharacter && m_drwaingContainer)
    {

        m_currentCharacter->getWeaponCreatorContainer().setPosition(target.getView().getCenter());
        target.draw(m_currentCharacter->getWeaponCreatorContainer(),
                    states);
        shape.setPosition(m_currentCharacter->getPosition());
        // draw the character's weapons collection


    }
    else if (m_drwaingContainer)
    {
        shape.setPosition(m_mousePosition);
    }
    target.draw(shape, states);
}

bool Team::onMouseClick(const MapVector &mousePosition)
{
    std::cout << "mouse clicked  -- " << mousePosition << std::endl;
    if (m_weapon)
    {
        m_weapon->handleMousePressed(mousePosition);
    }
    else if (m_currentCharacter)
    {
        WeaponCreator *weaponCreator =
                m_currentCharacter->
                        getWeaponCreatorContainer().
                        getWeaponCreator(mousePosition);
        if (weaponCreator)
        {
            m_weapon = weaponCreator->createWeapon(*m_currentCharacter);
        }
    }
    else if (m_drwaingContainer)
    {
        // choose a character
        for (auto character: m_characters)
        {

            if ((character->getPosition() -
                 MapVector(mousePosition)).getMagnitude() <
                character->getRadius())
            {
                m_currentCharacter = character;
                break;
            }
        }
    }
    return false;
}

bool Team::onMouseMove(const MapVector &mousePosition)
{
    m_mousePosition = mousePosition;
    if (m_weapon)
    {
        m_weapon->handleMouseMoved(mousePosition);
    }
    else if (m_currentCharacter)
    {
        // handle the character's weapons collection
    }
    return false;
}

bool Team::update(const sf::Time &deltaTime, bool allStopped)
{
    m_drwaingContainer = allStopped;
    if (m_weapon)
    {

        if (!m_weapon->isAlive())
        {
            bool done = m_weapon->turnEndded();
            m_weapon.reset();
            if (done)
            {
                m_currentCharacter = nullptr;
            }
            return done;
        }
        else
        {
            m_weapon->update(deltaTime);
        }
    }

    return false;
}


const PlayerColor &Team::getColor() const
{
    return m_color;
}

void Team::addCharacter(Character *character)
{
    m_characters.push_back(character);
}

bool Team::isDead() const
{
    return m_characters.empty();
}

