#include <SFML/Graphics.hpp>

class ParallaxLayer : public sf::Drawable
{
public:
    ParallaxLayer(const sf::Texture &texture,
                  const sf::FloatRect &mapRect,
                  float speed);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    const sf::Texture &m_texture;
    const sf::FloatRect m_mapRect;
    float m_speed;
};