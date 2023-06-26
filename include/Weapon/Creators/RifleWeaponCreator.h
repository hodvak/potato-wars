#pragma once

#include <functional>
#include "Weapon/Creators/WeaponCreator.h"
#include "MapObject/MovingMapObject.h"
#include "BombHandler.h"

/**
 * the class that creates rifle weapon
 */
class RifleWeaponCreator : public WeaponCreator
{
public:
    /**
     * regular constructor
     * @param amount the amount of rifle weapons to create
     * @param addMapObjectFunc the function to add map objects to the map
     * @param map the game map
     * @param bombHandler the bomb handler 
     */
    RifleWeaponCreator(int amount,
                       GameHelperData &gameHelperData);

    std::unique_ptr<Weapon> createWeaponImpl(Character &character) override;

    RifleWeaponCreator(const RifleWeaponCreator &other);

    [[nodiscard]] const sf::Texture &getTexture() const override;

    [[nodiscard]] sf::IntRect getTextureRect() const override;

};