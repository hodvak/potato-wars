#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "MapObject/Character.h"
#include "Weapon/Weapon.h"

class Team : public sf::Drawable
{
public:
    explicit Team(const PlayerColor &color);
    
    void removeDeadCharacters();
    
    // return true if done with their turn
    // called when it's their turn
    bool update(const sf::Time &deltaTime,bool allStopped);
    bool onMouseClick(const MapVector &mousePosition);
    bool onMouseMove(const MapVector &mousePosition);
    
    
    void addCharacter(Character* character);
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    [[nodiscard]] const PlayerColor &getColor() const;

    [[nodiscard]] bool isDead() const;

private:
    PlayerColor m_color;
    std::vector<Character*> m_characters;
    Character *m_currentCharacter;
    std::unique_ptr<Weapon> m_weapon;
    MapVector m_mousePosition;
    bool m_drwaingContainer = false;
};