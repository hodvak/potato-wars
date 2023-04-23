#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class MovingMapObject;

#include "Bomb.h"

void drawBomb(sf::Image &map,const Bomb &bomb);

class BombHandler
{

public:
    BombHandler();


    void addBomb(const Bomb &bomb);

    void update(sf::Image &map,
                std::vector<std::unique_ptr<MovingMapObject>> &objects);

private:
    std::vector<Bomb> m_bombs;

};
