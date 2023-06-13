#pragma once
#include "MapObject/Crates/Crate.h"
class HealthCrate : public Crate
{
public:
    HealthCrate(MapVector pos,GameMap *map);
    bool collideDD2(Character *other_object) override;
private:
    int health;
};
