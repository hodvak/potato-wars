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
    /**
     * radius of the Character
     */
    static const float RADIUS;
    
    /**
     * weight of the Character
     */
    static const float WEIGHT;
    
public:
    /**
     * create a Character in the given position
     * @param pos the position of the Character
     * @param map the map that the Character is in
     * @param bomb_handler BombHandler to add bombs to
     * @param color the color of the Character (Character)
     */
    Character(const MapVector &pos,
              const GameMap &map,
              BombHandler &bomb_handler,
              const PlayerColor &color);
    
    /**
     * update the Character according to the time that passed
     * @param deltaTime the time that passed since the last update
     */
    void update(const sf::Time &deltaTime) override;
    
    /**
     * function for double dispatch. need to be the same in all the 
     * MovingMapObject derived classes
     */
    bool collideDD1(MovingMapObject &other_object) override;
    
    /**
     * collideDD1 with a Character.
     */
    bool collideDD2(Character &other_object) override;
    
    /**
     * decrease the life of the Character
     * @param damage the amount of life to decrease
     */
    void damage(float damage);
    
    /**
     * draw the Character to the target
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    /**
     * add a WeaponCreator to the Character (to the WeaponCreatorContainer)
     * @param weaponCreator 
     */
    void addWeaponCreator(std::unique_ptr<WeaponCreator> &&weaponCreator);

    /**
     * get the WeaponCreatorContainer of the Character
     */
    [[nodiscard]] const WeaponCreatorContainer &getWeaponCreatorContainer() const;
    
    /**
     * get the WeaponCreatorContainer of the Character (non const)
     */
    [[nodiscard]] WeaponCreatorContainer &getWeaponCreatorContainer();
    
    /**
     * get the color of the Character
     */
    PlayerColor getColor() const;
    
    /**
     * get damage from the explosion
     * @param bomb the explosion
     */
    void exploded(const Explosion &bomb) override;




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
    
    /**
     * container of the WeaponCreators of the Character (all the weapons that
     * the Character can use)
     */
    WeaponCreatorContainer m_weaponCreatorContainer;
};