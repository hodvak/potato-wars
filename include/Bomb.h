#pragma once
#include <SFML/Graphics.hpp>

struct Bomb
{
    sf::Vector2f pos;
    float radius;
    float force;
};