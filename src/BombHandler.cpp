#include "BombHandler.h"
#include "MapObject/MovingMapObject.h"

BombHandler::BombHandler() = default;

void drawBomb(GameMap *map, const Explosion &bomb)
{
    map->bomb(bomb.pos, bomb.radius);
}

void BombHandler::addBomb(const Explosion &bomb)
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
        for (int i =  0;i<5;i++)
        {
            //add fragments on the circumference of the bomb
            m_addFragments(bomb.pos, {(float)bomb.radius, i * 90.f});
        }
    }
    m_bombs.clear();
}

void BombHandler::setAddFragments(
        std::function<void(MapVector, MapVector)> addFragments)
{
    m_addFragments = std::move(addFragments);

}
