#include <format>
#include "GameMap.h"
#include "resources_manager.h"

GameMap::GameMap(int levelNumber)
{

    m_mask = *resources_manager::getImage(
            std::vformat(resources_manager::PATH_LEVELS,
                         std::make_format_args(levelNumber)));
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
    const sf::Texture *sunset1 = resources_manager::getTexture(
            resources_manager::IMG_SUNSET1_PATH);
    const sf::Texture *sunset2 = resources_manager::getTexture(
            resources_manager::IMG_SUNSET2_PATH);
    const sf::Texture *sunset3 = resources_manager::getTexture(
            resources_manager::IMG_SUNSET3_PATH);
    const sf::Texture *sunset4 = resources_manager::getTexture(
            resources_manager::IMG_SUNSET4_PATH);
    const sf::Texture *sunset5 = resources_manager::getTexture(
            resources_manager::IMG_SUNSET5_PATH);
    const sf::Texture *sunset6 = resources_manager::getTexture(
            resources_manager::IMG_SUNSET6_PATH);
    const sf::Texture *sunset7 = resources_manager::getTexture(
            resources_manager::IMG_SUNSET7_PATH);
    const sf::Texture *sunset8 = resources_manager::getTexture(
            resources_manager::IMG_SUNSET8_PATH);
    const sf::Texture *sunset9 = resources_manager::getTexture(
            resources_manager::IMG_SUNSET9_PATH);
    m_layers.emplace_back(sunset1,
                          sf::Vector2f(sunset1->getSize().x, sunset1->getSize().y),
                          sf::Vector2f(m_mask.getSize().x, m_mask.getSize().y),
                          0.9);
    m_layers.emplace_back(sunset2,
                          sf::Vector2f(sunset2->getSize().x, sunset2->getSize().y),
                          sf::Vector2f(m_mask.getSize().x, m_mask.getSize().y),
                          0.8);
    m_layers.emplace_back(sunset3,
                          sf::Vector2f(sunset3->getSize().x, sunset3->getSize().y),
                          sf::Vector2f(m_mask.getSize().x, m_mask.getSize().y),
                          0.7);
    m_layers.emplace_back(sunset4,
                          sf::Vector2f(sunset4->getSize().x, sunset4->getSize().y),
                          sf::Vector2f(m_mask.getSize().x, m_mask.getSize().y),
                          0.6);
    m_layers.emplace_back(sunset5,
                          sf::Vector2f(sunset5->getSize().x, sunset5->getSize().y),
                          sf::Vector2f(m_mask.getSize().x, m_mask.getSize().y),
                          0.5);
    m_layers.emplace_back(sunset6,
                          sf::Vector2f(sunset6->getSize().x, sunset6->getSize().y),
                          sf::Vector2f(m_mask.getSize().x, m_mask.getSize().y),
                          0.4);
    m_layers.emplace_back(sunset7,
                          sf::Vector2f(sunset7->getSize().x, sunset7->getSize().y),
                          sf::Vector2f(m_mask.getSize().x, m_mask.getSize().y),
                          0.3);
    m_layers.emplace_back(sunset8,
                          sf::Vector2f(sunset8->getSize().x, sunset8->getSize().y),
                          sf::Vector2f(m_mask.getSize().x, m_mask.getSize().y),
                          0.2);
    m_layers.emplace_back(sunset9,
                          sf::Vector2f(sunset9->getSize().x, sunset9->getSize().y),
                          sf::Vector2f(m_mask.getSize().x, m_mask.getSize().y),
                          0.f);
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
    for (auto &layer: m_layers)
    {
        layer.setPosition(m_target->getView().getCenter());
        layer.update(deltaTime);
    }
}

void GameMap::setTarget(const sf::RenderTarget *target)
{
    m_target = target;
}
