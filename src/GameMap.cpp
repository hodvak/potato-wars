#include <format>
#include "GameMap.h"
#include "resources_manager.h"

GameMap::GameMap(const Level &level) : m_level(level)
{

    m_mask = *resources_manager::getImage(
            std::vformat(resources_manager::PATH_LEVELS,
                         std::make_format_args(level.levelNumber)));

    m_ground = resources_manager::getImage(
            "resources/Images/MapImages/" + level.groundTexture
    );

    m_width = m_mask.getSize().x;
    m_height = m_mask.getSize().y;

    m_display.create(m_width, m_height);
    for (unsigned int x = 0; x < m_width; ++x)
    {
        for (unsigned y = 0; y < m_height; ++y)
        {
            sf::Color maskColor = m_mask.getPixel(x, y);
            if (maskColor == sf::Color::White)
            {
                sf::Color groundColor = m_ground->getPixel(x, y);
                m_display.setPixel(x, y, groundColor);
            }
            else
            {

                m_display.setPixel(x, y, sf::Color::Transparent);
            }
        }
    }
    for (int i = 1; i <= level.numberOfLayers; ++i)
    {
        auto &texture = resources_manager::get<sf::Texture>(
                "resources/Images/MapImages/" + level.layersDir + "/" +
                std::to_string(i) + ".png"
        );
        m_layers.emplace_back(
                texture,
                sf::FloatRect (
                    -200.f,
                    -200.f,
                    (float) m_width + 400.f,
                    (float) m_height + 400.f
                ),
                (0.9 - i * 0.1)

        );
    }
}

void GameMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite;


    sf::Texture texture;
    texture.loadFromImage(m_display);
    sprite.setTexture(texture);

    for (int i = m_layers.size(); i > 0; --i)
    {
        target.draw(m_layers[i - 1], states);
    }

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
                int x = (int) (pos.x + (float) i);
                int y = (int) (pos.y + (float) j);
                if (x >= 0 && x < m_width && y >= 0 && y < m_height)
                {
                    m_mask.setPixel(x, y, sf::Color::Black);
                    m_display.setPixel(x, y, sf::Color::Transparent);
                }
            }
        }
    }
}

const sf::Image &GameMap::getMask() const
{
    return m_mask;
}

void GameMap::update(const sf::Time &deltaTime)
{
    
}

void GameMap::setTarget(const sf::RenderTarget *target)
{
    m_target = target;
}
