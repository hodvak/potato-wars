#pragma once

#include <SFML/Graphics.hpp>
#include "map_vector.h"

/**
 * a bomb class for the BombHandler
 */
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