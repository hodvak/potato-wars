#include "BombHandler.h"
#include "MapObject/MovingMapObject.h"

BombHandler::BombHandler() = default;

void drawBomb(GameMap *map, const Bomb &bomb)
{
    map->drawCircle(bomb.pos, bomb.radius);
}

void BombHandler::addBomb(const Bomb &bomb)
{
    m_bombs.push_back(bomb);
}

void BombHandler::update(GameMap *map,
                         std::vector<std::unique_ptr<MovingMapObject>> &objects)
{
    for (auto &bomb: m_bombs)
    {
        drawBomb(map, bomb);
        for(const auto & object : objects)
        {
            object->exploded(bomb);
        }
    }
    m_bombs.clear();
}

