#pragma once

#include "MapObject/Crates/Crate.h"
#include "MapObject/Character.h"

class HealthCrate : public Crate
{
public:
    HealthCrate(const MapVector &pos,
                GameHelperData &gameHelperData,float health = 50.f);
    
    ~HealthCrate() override = default;
    bool collideDD1(MovingMapObject &otherObject) override;
    bool collideDD2(Character &otherObject) override;
    
private:
    float health;

};
