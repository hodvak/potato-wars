#include "GameMap.h"
#include "resources_manager.h"

GameMap::GameMap(const std::string &levelName)
{
    m_mask = *resources_manager::getImage(
            "resources/Levels/" + levelName + "/map.bmp");
    m_sky = resources_manager::getImage(
            "resources/Images/MapImages/sky.bmp");
    m_ground = resources_manager::getImage(
            "resources/Images/MapImages/ground.bmp");

    m_width = m_mask.getSize().x;
    m_height = m_mask.getSize().y;

    m_display.create(m_width, m_height);
    for (int x = 0; x < m_width; ++x)
    {
        for (int y = 0; y < m_height; ++y)
        {
            sf::Color maskColor = m_mask.getPixel(x, y);
            if (maskColor == sf::Color::White)
            {
                sf::Color groundColor = m_ground->getPixel(x, y);
                m_display.setPixel(x, y, groundColor);
            }
            else
            {
                sf::Color skyColor = m_sky->getPixel(x, y);
                m_display.setPixel(x, y, skyColor);
            }
        }
    }
}

void GameMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite;
    sf::Texture texture;
    texture.loadFromImage(m_display);
    sprite.setTexture(texture);
    target.draw(sprite, states);
}

void GameMap::bomb(const MapVector &pos, int radius)
{
    int radius_squared = radius * radius; // to avoid sqrt

    for (int i = -radius; i <= radius; ++i)
    {
        for (int j = -radius; j <= radius; ++j)
        {
            if (i * i + j * j <= radius_squared)
            {
                int x = (int)(pos.x + (float)i);
                int y = (int)(pos.y + (float)j);
                if (x >= 0 && x < m_width && y >= 0 && y < m_height)
                {
                    m_mask.setPixel(x, y, sf::Color::Black);
                    m_display.setPixel(x, y, m_sky->getPixel(x, y));
                }
            }
        }
    }
}

const sf::Image &GameMap::getMask() const
{
    return m_mask;
}
