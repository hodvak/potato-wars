#pragma once

#include <SFML/Graphics.hpp>
#include "MapVector.h"

/**
 * a struct class for the BombHandler
 * that represent an explosion
 */
struct Explosion
{
    Explosion(MapVector pos, int radius, float force) :
            pos(pos),
            radius(radius),
            force(force)
    {};
    MapVector pos;
    int radius;
    float force;
};