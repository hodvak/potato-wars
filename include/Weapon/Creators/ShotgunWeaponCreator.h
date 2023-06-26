#pragma once

#include <functional>
#include "Weapon/Creators/WeaponCreator.h"
#include "MapObject/MovingMapObject.h"
#include "BombHandler.h"

/**
 * the class that creates rifle weapon
 */
class ShotgunWeaponCreator : public WeaponCreator
{
public:
    ShotgunWeaponCreator(int amount,
                         GameHelperData &gameHelperData);

    std::unique_ptr<Weapon> createWeaponImpl(Character &character) override;

    ShotgunWeaponCreator(const ShotgunWeaponCreator &other);

    [[nodiscard]] const sf::Texture &getTexture() const override;

    [[nodiscard]] sf::IntRect getTextureRect() const override;

private:
};