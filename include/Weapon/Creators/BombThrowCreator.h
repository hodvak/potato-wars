#pragma once
#include "WeaponCreator.h"
#include "MapObject/Bomb.h"
#include <functional>

class BombThrowCreator : public WeaponCreator
{
public:
    BombThrowCreator(int amount,
                     const std::function<void(
                             std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
                     const GameMap &map,
                     BombHandler &bombHandler);

    BombThrowCreator(const BombThrowCreator &other);

    std::unique_ptr<Weapon> createWeaponImpl(Character &character) override;

    [[nodiscard]] const sf::Texture &getTexture() const override;

    [[nodiscard]] sf::IntRect getTextureRect() const override;

    [[nodiscard]] std::unique_ptr<WeaponCreator> copy() const override;

private:
        const GameMap &m_map;
        BombHandler &m_bombHandler;
        std::function<void(std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
};