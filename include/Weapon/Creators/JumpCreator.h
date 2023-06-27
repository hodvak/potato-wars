#pragma once
#include "WeaponCreator.h"
#include "MapObject/MovingMapObject.h"
#include <functional>
class JumpCreator : public WeaponCreator
{
public:
    JumpCreator(int amount,
                GameHelperData &gameHelperData);
    void addAmount(int amount) override;
    [[nodiscard]] const sf::Texture &getTexture() const override;
    [[nodiscard]] sf::IntRect getTextureRect() const override;
private:
    std::unique_ptr<Weapon> createWeaponImpl(Character &character) override;
};