#pragma once

#include <functional>
#include "Weapon/Creators/WeaponCreator.h"
#include "MapObject/MovingMapObject.h"


class StoneThrowCreator : public WeaponCreator
{
public:
    StoneThrowCreator(int amount,
                      GameHelperData &gameHelperData);

    StoneThrowCreator(const StoneThrowCreator &other);

    std::unique_ptr<Weapon> createWeaponImpl(Character &character) override;

    [[nodiscard]] const sf::Texture &getTexture() const override;

    [[nodiscard]] sf::IntRect getTextureRect() const override;

};