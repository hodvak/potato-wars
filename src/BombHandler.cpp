#include "BombHandler.h"
#include "moving_map_object.h"
BombHandler::BombHandler()
{

}

void BombHandler::addBomb(const Bomb &bomb)
{
    m_bombs.push_back(bomb);
}

void BombHandler::update(Map *map,
                         std::vector<std::unique_ptr<MovingMapObject>> &objects)
{
    for (auto &bomb: m_bombs)
    {
        drawBomb(map, bomb);
        for (int i = 0; i < objects.size(); ++i)
        {
            objects[i]->exploded(bomb);
        }

    }
    m_bombs.clear();
}
void drawBomb(Map *map,const Bomb &bomb)
{
    map->drawCircle(bomb.pos, bomb.radius);
}
