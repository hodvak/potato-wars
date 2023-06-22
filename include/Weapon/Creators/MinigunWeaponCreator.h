#pragma once

#include <functional>
#include "Weapon/Creators/WeaponCreator.h"
#include "MapObject/MovingMapObject.h"
#include "BombHandler.h"

/**
 * the class that creates rifle weapon
 */
class MinigunWeaponCreator : public WeaponCreator
{
public:
    /**
     * regular constructor
     * @param amount the amount of rifle weapons to create
     * @param addMapObjectFunc the function to add map objects to the map
     * @param map the game map
     * @param bombHandler the bomb handler 
     */
    MinigunWeaponCreator(int amount,
                       const std::function<void(
                               std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
                       const GameMap &map,
                       BombHandler &bombHandler);

    std::unique_ptr<Weapon> createWeaponImpl(const Character &character) override;

    MinigunWeaponCreator(const MinigunWeaponCreator &other);

    [[nodiscard]] const sf::Texture *getTexture() const override;

    [[nodiscard]] std::unique_ptr<WeaponCreator> copy() const override;

    [[nodiscard]] sf::IntRect getTextureRect() const override;

private:
    const GameMap &m_map;
    std::function<void(std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
    BombHandler &m_bombHandler;
};