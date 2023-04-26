#pragma once

#include <SFML/Graphics.hpp>
#include "MapVector.h"

struct Bomb
{
    Bomb(MapVector pos, int radius, float force) :
            pos(pos),
            radius(radius),
            force(force)
    {};
    MapVector pos;
    int radius;
    float force;
};