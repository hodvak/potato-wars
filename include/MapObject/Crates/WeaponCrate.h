#pragma once
#include "Crate.h"
#include "MapObject/Character.h"
class WeaponCrate : public Crate
{
public:
    WeaponCrate(MapVector pos,GameMap *map,std::unique_ptr<WeaponCreator> &&weaponCreator);
    bool collideDD2(Character *other_object) override;
private:
    std::unique_ptr<WeaponCreator> m_weaponCreator;
};