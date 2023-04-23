#pragma once
#include <SFML/Graphics.hpp>
#include "MapVector.h"

struct Bomb
{
    MapVector pos;
    float radius;
    float force;
};