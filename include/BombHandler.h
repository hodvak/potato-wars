#pragma once
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <vector>

class MovingMapObject;

#include "Bomb.h"

void drawBomb(Map *map,const Bomb &bomb);

class BombHandler
{

public:
    BombHandler();


    void addBomb(const Bomb &bomb);

    void update(Map *map,
                std::vector<std::unique_ptr<MovingMapObject>> &objects);

private:
    std::vector<Bomb> m_bombs;

};
