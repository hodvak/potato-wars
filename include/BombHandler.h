#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class MovingMapObject;

#include "Bomb.h"

void drawBomb(sf::Image &map, Bomb &bomb);

class BombHandler
{

public:
    BombHandler();


    void addBomb(Bomb bomb);

    void update(sf::Image &map,
                std::vector<std::unique_ptr<MovingMapObject>> &objects);

private:
    std::vector<Bomb> m_bombs;

};
