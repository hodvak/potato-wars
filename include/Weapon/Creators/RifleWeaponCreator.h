#pragma once

#include <functional>
#include "Weapon/Creators/WeaponCreator.h"
#include "MapObject/MovingMapObject.h"
#include "BombHandler.h"

class RifleWeaponCreator : public WeaponCreator
{
public:
    RifleWeaponCreator(int amount,
                       GameMap *map,
                       const std::function<void(
                               std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
                       BombHandler &bombHandler);

    RifleWeaponCreator(const RifleWeaponCreator &other);

    std::unique_ptr<Weapon> createWeaponImpl(Character &character) override;

    [[nodiscard]] const sf::Texture *getTexture() const override;

    [[nodiscard]] std::unique_ptr<WeaponCreator> copy() const override;

    [[nodiscard]] sf::IntRect getTextureRect() const override;

private:
    GameMap *m_map;
    std::function<void(std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
    BombHandler &m_bombHandler;
};