#pragma once

#include "MovingMapObject.h"
#include "GameMap.h"
#include "MapObject/Textures/playerTexture.h"
#include "Weapon/WeaponCreatorContainer.h"

/**
 * a Character is one of the players characters
 * each character has its own player color
 */
class Character : public MovingMapObject
{
private:
    static const float RADIUS;
    static const float WEIGHT;
    
public:
    /**
     * create a Character in the given position
     * @param pos the position of the Character
     * @param map the map that the Character is in
     * @param bomb_handler BombHandler to add bombs to
     * @param color the color of the Character (Character)
     */
    Character(sf::Vector2f pos,
              GameMap *map,
              BombHandler *bomb_handler,
              PlayerColor color);
    
    /**
     * update the Character according to the time that passed
     * @param deltaTime the time that passed since the last update
     */
    void update(const sf::Time &deltaTime) override;
    
    /**
     * function for double dispatch. need to be the same in all the 
     * MovingMapObject derived classes
     */
    bool collideDD1(MovingMapObject *other_object) override;
    
    /**
     * collideDD1 with a Character.
     */
    bool collideDD2(Character *other_object) override;
    
    /**
     * decrease the life of the Character
     * @param damage the amount of life to decrease
     */
    void damage(float damage);
    
    /**
     * draw the Character to the target
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    void addWeaponCreator(std::unique_ptr<WeaponCreator> &&weaponCreator);

    [[nodiscard]] const WeaponCreatorContainer &getWeaponCreatorContainer() const;
    [[nodiscard]] WeaponCreatorContainer &getWeaponCreatorContainer();
    
    /**
     * get the color of the Character
     */
    PlayerColor getColor() const;

private:
    
    /**
     * texture of the Character
     */
    PlayerTexture m_texture;
    
    /**
     * life of the Character (in [0, 1])
     */
    float m_life;
    
    /**
     * the color of the Character
     */
    PlayerColor m_color;
    
    WeaponCreatorContainer m_weaponCreatorContainer;
    

};