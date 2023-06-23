#pragma once

#include <functional>
#include "Weapon/Creators/WeaponCreator.h"
#include "MapObject/MovingMapObject.h"


class StoneThrowCreator : public WeaponCreator
{
public:
    StoneThrowCreator(int amount,
                      const std::function<void(
                              std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
                      const GameMap &map,
                      BombHandler &bombHandler);

    StoneThrowCreator(const StoneThrowCreator &other);

    std::unique_ptr<Weapon> createWeaponImpl(Character &character) override;

    [[nodiscard]] const sf::Texture &getTexture() const override;

    [[nodiscard]] sf::IntRect getTextureRect() const override;

    [[nodiscard]] std::unique_ptr<WeaponCreator> copy() const override;

    [[nodiscard]] const GameMap &getMap() const;

private:

    const GameMap &m_map;
    BombHandler &m_bombHandler;
    std::function<void(std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
};