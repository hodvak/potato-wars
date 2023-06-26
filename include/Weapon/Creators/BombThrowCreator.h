#pragma once
#include "WeaponCreator.h"
#include "MapObject/Bomb.h"
#include <functional>

class BombThrowCreator : public WeaponCreator
{
public:
    BombThrowCreator(int amount,
                     GameHelperData &gameHelperData);

    BombThrowCreator(const BombThrowCreator &other);

    std::unique_ptr<Weapon> createWeaponImpl(Character &character) override;

    [[nodiscard]] const sf::Texture &getTexture() const override;

    [[nodiscard]] sf::IntRect getTextureRect() const override;


private:
};