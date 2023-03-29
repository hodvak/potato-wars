#include <string>
#include <SFML/Graphics.hpp>

const int WIDTH = 1080;
const int HEIGHT = 720;

class Map 
{
public:
    Map(std::string path);

    void loadMap(std::string path);

    char operator()(int x, int y) const;

    char operator[](const sf::Vector2i &) const;

    char &operator()(int x, int y);

    char &operator[](const sf::Vector2i &);

private:
    char m_map[WIDTH][HEIGHT];
    enum t_map
    {
        EMPTY = 'E', WALL = '#', GRASS = 'G', BURN = 'B'
    };


};