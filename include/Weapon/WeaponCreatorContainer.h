#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <optional>
#include "MapVector.h"
#include "Weapon/Creators/WeaponCreator.h"

/**
 * a class that represents a container of weapon creators
 * used to create weapons in the game.
 * each Character has a WeaponCreatorContainer that contains all the weapons
 * that the character can use
 */
class WeaponCreatorContainer : public sf::Drawable
{
public:
    /**
     * regular constructor
     */
    WeaponCreatorContainer(GameHelperData &gameHelperData);
    
    /**
     * add a weapon creator to the container
     * @param weaponCreator the weapon creator to add
     */
    void addWeaponCreator(std::unique_ptr<WeaponCreator> &&weaponCreator);
    void addJumpCreator(std::unique_ptr<WeaponCreator> &&weaponCreator);
    /**
     * get the weapon creator that the mouse is on
     */
    WeaponCreator * getWeaponCreator();
    
    /**
     * draw the container on the target
     * @param target the target to draw on
     * @param states the states to draw with
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    
private:
    
    /**
     * list of weapon creators
     */
    std::vector<std::unique_ptr<WeaponCreator>> m_weaponCreators;


    GameHelperData &m_gameHelperData;


    static const sf::Vector2u TABLE_SIZE;
    static const MapVector RECT_PERCENTAGE;



};