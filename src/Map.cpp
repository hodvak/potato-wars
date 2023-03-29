#include "Map.h"
#include <iostream>
#include <fstream>

Map::Map(std::string path)
{
    loadMap(path);
}


void Map::loadMap(std::string path)
{
    std::ifstream file(path);
    if (file.is_open())
    {
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                file >> m_map[j][i];
            }
        }
    }
    else
    {
        std::cout << "Error: Could not open file" << std::endl;
    }
    file.close();
}



char Map::operator()(int x, int y) const{
    return m_map[x][y];
}

char Map::operator[](const sf::Vector2i &v) const{
    return m_map[v.x][v.y];
}

char &Map::operator()(int x, int y)
{
    return m_map[x][y];
}

char &Map::operator[](const sf::Vector2i &v)
{
    return m_map[v.x][v.y];
}
