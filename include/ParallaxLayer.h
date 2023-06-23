#include <SFML/Graphics.hpp>

class ParallaxLayer : public sf::Drawable
{
public:
    ParallaxLayer(const sf::Texture *texture, const sf::Vector2f &size,
                  const sf::Vector2f &position, float speed);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update(const sf::Time &deltaTime);

    void setPosition(const sf::Vector2f &position);

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_size;
    sf::Vector2f m_position;
    float m_speed;
};