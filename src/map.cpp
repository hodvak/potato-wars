#include "map.h"

Map::Map(const sf::Image &mask, const sf::Image &sky, const sf::Image &ground) :
        m_mask(mask),
        m_sky(sky),
        m_ground(ground)
{

    m_display.create(WIDTH, HEIGHT);
    for (int i = 0; i < WIDTH; ++i)
    {
        for (int j = 0; j < HEIGHT; ++j)
        {
            sf::Color maskColor = mask.getPixel(i, j);
            if (maskColor == sf::Color::Black)
            {
                sf::Color skyColor = sky.getPixel(i, j);
                m_display.setPixel(i, j, skyColor);
            }
            else
            {
                sf::Color groundColor = ground.getPixel(i, j);
                m_display.setPixel(i, j, groundColor);
            }
        }
    }
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite;
    sf::Texture texture;
    texture.loadFromImage(m_display);
    sprite.setTexture(texture);
    target.draw(sprite, states);
}

void Map::drawCircle(MapVector pos, int radius)
{
    int radius_squared = radius * radius;
    for (int i = -radius; i < radius; ++i)
    {
        for (int j = -radius; j < radius; ++j)
        {
            if (i * i + j * j < radius_squared)
            {
                int x = (int) pos.x + i;
                int y = (int) pos.y + j;
                if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
                {
                    m_mask.setPixel(x, y, sf::Color::Black);
                    m_display.setPixel(x, y, m_sky.getPixel(x, y));
                }
            }
        }
    }
}

const sf::Image *Map::get_mask() const
{
    return &m_mask;
}
