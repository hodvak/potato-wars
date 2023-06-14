#pragma once

#include <functional>
#include "Weapon/Creators/WeaponCreator.h"
#include "MapObject/MovingMapObject.h"


class StoneThrowCreator : public WeaponCreator
{
public:
    StoneThrowCreator(int amount,
                      GameMap *map,
                      const std::function<void(
                              std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc);

    StoneThrowCreator(const StoneThrowCreator &other);

    std::unique_ptr<Weapon> createWeaponImpl(Character &character) override;

    [[nodiscard]] const sf::Texture *getTexture() const override;

    [[nodiscard]] sf::IntRect getTextureRect() const override;

    [[nodiscard]] std::unique_ptr<WeaponCreator> copy() const override;

    GameMap *getMap() const;

private:

    GameMap *m_map;
    std::function<void(std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
};