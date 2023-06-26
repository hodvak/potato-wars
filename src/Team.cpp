#include "Team.h"

Team::Team(const PlayerColor &color, GameHelperData &helperData) :
        m_currentCharacter(nullptr),
        m_weapon(nullptr),
        m_color(color),
        m_helperData(helperData)
{

}


bool Team::removeDeadCharacters()
{
    bool courentCharacterIsDead = false;
    std::erase_if(m_characters, [&](Character *character)
    {
        if (m_currentCharacter == character && !character->isAlive())
        {
            m_currentCharacter = nullptr;
            courentCharacterIsDead = true;
        }
        return !character->isAlive();
    });
    return courentCharacterIsDead;
}

void Team::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::CircleShape shape(10);
    shape.setOrigin(10, 10);
    sf::Color color = ::getColor(m_color);
    color.a = 100;


    shape.setFillColor(color);
    if (m_currentCharacter)
    {
        shape.setPosition(m_currentCharacter->getPosition());
    }
    else
    {
        shape.setPosition(m_helperData.getMousePositionInMap());
    }
    
    if (m_weapon)
    {
        target.draw(*m_weapon, states);
    }
    else if (m_currentCharacter && m_drawingContainer)
    {

        m_currentCharacter->getWeaponCreatorContainer().setPosition(target.getView().getCenter());
        target.draw(m_currentCharacter->getWeaponCreatorContainer(),
                    states);
        shape.setPosition(m_currentCharacter->getPosition());
        // draw the character's weapons collection
    }
    target.draw(shape, states);
    
}

bool Team::onMouseClick()
{

    if (m_weapon)
    {
        m_weapon->handleMousePressed(m_helperData.getMousePositionInMap());
    }
    else if (m_currentCharacter)
    {
        WeaponCreator *weaponCreator =
                m_currentCharacter->
                        getWeaponCreatorContainer().
                        getWeaponCreator(m_helperData.getMousePositionInMap());
        if (weaponCreator)
        {
            m_weapon = weaponCreator->createWeapon(*m_currentCharacter);
        }
    }
    else if (m_drawingContainer)
    {
        // choose a character
        for (auto character: m_characters)
        {

            if ((character->getPosition() -
                 MapVector(m_helperData.getMousePositionInMap())).getMagnitude() <
                character->getRadius())
            {
                m_currentCharacter = character;
                break;
            }
        }
    }
    return false;
}


bool Team::update(const sf::Time &deltaTime, bool allStopped)
{
    m_drawingContainer = allStopped;
    if (m_weapon)
    {

        if (!m_weapon->isAlive())
        {
            bool done = m_weapon->turnEnder();
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
    if (m_weapon)
    {
        m_weapon->handleMouseMoved(m_helperData.getMousePositionInMap());
    }
    else if (m_currentCharacter)
    {
        // handle the character's weapons collection
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

