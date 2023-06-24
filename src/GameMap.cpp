#include <format>
#include "GameMap.h"
#include "resources_manager.h"

GameMap::GameMap(int levelNumber)
{

    m_mask = *resources_manager::getImage(std::vformat(resources_manager::PATH_LEVELS, std::make_format_args(levelNumber)));
    m_sky = resources_manager::getImage(
            "resources/Images/MapImages/sky2.jpg"
    );
    m_ground = resources_manager::getImage(
            resources_manager::IMG_GROUND_PATH
    );

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

                m_display.setPixel(x, y, sf::Color::Transparent);
            }
        }
    }
    const sf::Texture *texture1 = resources_manager::getTexture(
            resources_manager::IMG_LAYER1_PATH);
    const sf::Texture *texture2 = resources_manager::getTexture(
            resources_manager::IMG_LAYER2_PATH);
    const sf::Texture *texture3 = resources_manager::getTexture(
            resources_manager::IMG_LAYER3_PATH);
    const sf::Texture *texture4 = resources_manager::getTexture(
            resources_manager::IMG_LAYER4_PATH);
    m_layers.emplace_back(texture1,
                          sf::Vector2f(m_mask.getSize().x+200,
                                       m_mask.getSize().y+200),
                          sf::Vector2f(m_width, m_height),
                          0.8);
    m_layers.emplace_back(texture2,
                          sf::Vector2f(m_mask.getSize().x+200,
                                       m_mask.getSize().y+200),
                          sf::Vector2f(m_width, m_height),
                          0.6);
    m_layers.emplace_back(texture3,
                          sf::Vector2f(m_mask.getSize().x+200,
                                       m_mask.getSize().y+200),
                          sf::Vector2f(m_width, m_height),
                          0.4);
    m_layers.emplace_back(texture4,
                            sf::Vector2f(m_mask.getSize().x+200,
                                         m_mask.getSize().y+200),
                            sf::Vector2f(m_width, m_height),
                            0);
}

void GameMap::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::Sprite sprite;


    sf::Texture texture;
    texture.loadFromImage(m_display);
    sprite.setTexture(texture);

for (int i = m_layers.size();i>0;--i)
{
    target.draw(m_layers[i-1],states);
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
//    for (auto &layer: m_layers)
//    {
//        layer.setPosition(m_target->getView().getCenter());
//        layer.update(deltaTime);
//    }
}

void GameMap::setTarget(const sf::RenderTarget *target)
{
//    m_target = target;
}
