#include "object.h"
class Ball : public sf::Drawable
{
public:
    Ball();
    Ball(sf::Vector2f);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update() ;
    void move(sf::Vector2i moveTo);
    void setRadius(int radius);
    sf::Vector2f getPosition() const;
private:
    sf::CircleShape m_shape;

};