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
     * @param size the size of the container
     * @param position the position of the container
     */
    WeaponCreatorContainer(const MapVector &size, const MapVector &position);
    
    /**
     * add a weapon creator to the container
     * @param weaponCreator the weapon creator to add
     */
    void addWeaponCreator(std::unique_ptr<WeaponCreator> &&weaponCreator);
    
    /**
     * get the weapon creator that the mouse is on
     */
    WeaponCreator * getWeaponCreator(sf::Vector2f mousePosition);
    
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
    
    /**
     * the size of the container
     */
    MapVector m_size;
    
    /**
     * the position of the container (left top corner)
     */
    MapVector m_position;
    
};