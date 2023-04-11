#include "BombHandler.h"
#include "moving_map_object.h"
BombHandler::BombHandler()
{

}

void BombHandler::addBomb(Bomb bomb)
{
    m_bombs.push_back(bomb);
}

void BombHandler::update(sf::Image &map,
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
void drawBomb(sf::Image &map, Bomb &bomb)
{
    for (int i = 0; i < map.getSize().x; ++i)
    {
        for (int j = 0; j < map.getSize().y; ++j)
        {
            if (sqrt(pow(i - bomb.pos.x, 2) + pow(j - bomb.pos.y, 2)) < bomb.radius)
            {
                map.setPixel(i, j, sf::Color::Black);
            }
        }
    }
}
