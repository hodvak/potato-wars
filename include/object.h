#include <SFML/Graphics.hpp>
class Object: public sf::Drawable
{
public:
    Object();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)
    {};
    virtual void update() = 0;
    virtual void move(sf::Vector2i) = 0;

private:
    sf::Vector2i m_position;
    sf::Vector2i m_velocity;
    sf::Vector2i m_acceleration;
    int m_width;
    int m_height;
    bool m_isAlive;
    bool m_isVisible;
    bool m_isMoving;
};