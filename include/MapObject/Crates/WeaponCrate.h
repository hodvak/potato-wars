#pragma once

#include "Crate.h"
#include "MapObject/Character.h"

class WeaponCrate : public Crate
{
public:
    WeaponCrate(const MapVector &pos,
                std::unique_ptr<WeaponCreator> &&weaponCreator,
                const GameMap &map,
                BombHandler &bombHandler);

    bool collideDD1(MovingMapObject &otherObject) override;
    bool collideDD2(Character &otherObject) override;

private:
    std::unique_ptr<WeaponCreator> m_weaponCreator;
};