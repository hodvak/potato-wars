#include "Team.h"

Team::Team(const PlayerColor &color):
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
    shape.setFillColor(color);
    if(m_weapon)
    {
        target.draw(*m_weapon, states);
    }
    else if(m_currentCharacter)
    {
        target.draw(m_currentCharacter->getWeaponCreatorContainer(), states);
        shape.setPosition(m_currentCharacter->getPosition());
        // draw the character's weapons collection
        
    }
    else
    {
        shape.setPosition(m_mousePosition);
    }
    target.draw(shape, states);
}

bool Team::onMouseClick(const sf::Vector2f &mousePosition)
{
    if(m_weapon)
    {
        m_weapon->handleMousePressed(mousePosition);
    }
    else if(m_currentCharacter)
    {
        std::optional<WeaponCreator *> weaponCreator = 
                m_currentCharacter->
                getWeaponCreatorContainer().
                getWeaponCreator(mousePosition);
        if(weaponCreator)
        {
            m_weapon = (*weaponCreator)->createWeapon(*m_currentCharacter);
        }
        // handle the character's weapons collection
    }
    else
    {
        // choose a character
        for(auto character : m_characters)
        {
            std::cout << (character->getPosition() - MapVector(mousePosition)).getMagnitude() << std::endl;
            if((character->getPosition() - MapVector(mousePosition)).getMagnitude() < character->getRadius())
            {
                m_currentCharacter = character;
                break;
            }
        }
    }
    return false;
}

bool Team::onMouseMove(const sf::Vector2f &mousePosition)
{
    m_mousePosition = mousePosition;
    if(m_weapon)
    {
        m_weapon->handleMouseMoved(mousePosition);
    }
    else if(m_currentCharacter)
    {
        // handle the character's weapons collection
    }
    return false;
}

bool Team::update(const sf::Time &deltaTime)
{
    if(m_weapon)
    {
        m_weapon->update(deltaTime);
        if(!m_weapon->isAlive())
        {
            m_weapon.reset();
            m_currentCharacter = nullptr;
            return true;
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

