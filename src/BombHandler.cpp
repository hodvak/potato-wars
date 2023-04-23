#include "BombHandler.h"
#include "moving_map_object.h"
BombHandler::BombHandler()
{

}

void BombHandler::addBomb(const Bomb &bomb)
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
void drawBomb(sf::Image &map,const Bomb &bomb)
{
    float radius_2 = bomb.radius * bomb.radius;
    for (int i = -(int)bomb.radius; i <= (int)bomb.radius; ++i)
    {
        for (int j = -(int)bomb.radius; j <= (int)bomb.radius; ++j)
        {
            if (i*i+j*j < radius_2)
            {
                map.setPixel((int)bomb.pos.x+i,(int) bomb.pos.y+j, sf::Color::Black);
            }
        }
    }
}
