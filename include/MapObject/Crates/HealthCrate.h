#pragma once

#include "MapObject/Crates/Crate.h"
#include "MapObject/Character.h"

class HealthCrate : public Crate
{
public:
    HealthCrate(const MapVector &pos,
                const GameMap &map,
                BombHandler &bombHandler);
    ~HealthCrate() override = default;
    bool collideDD1(MovingMapObject &otherObject) override;
    bool collideDD2(Character &otherObject) override;
    
private:
    int health;
};
