#include "bomb_handler.h"
#include "moving_map_object.h"

BombHandler::BombHandler() = default;

void draw_bomb(Map *map, const Bomb &bomb)
{
    map->drawCircle(bomb.pos, bomb.radius);
}

void BombHandler::add_bomb(const Bomb &bomb)
{
    m_bombs.push_back(bomb);
}

void BombHandler::update(Map *map,
                         std::vector<std::unique_ptr<MovingMapObject>> &objects)
{
    for (auto &bomb: m_bombs)
    {
        draw_bomb(map, bomb);
        for(const auto & object : objects)
        {
            object->exploded(bomb);
        }
    }
    m_bombs.clear();
}

