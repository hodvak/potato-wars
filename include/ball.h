#include "object.h"

class Ball : public sf::Drawable
{
public:
    explicit Ball(sf::Vector2f pos = {0,0}, float radius = 10);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void update();

    void move(sf::Vector2i moveTo);

    void setRadius(int radius);

    sf::Vector2f getPosition() const;

private:
    sf::CircleShape m_shape;

};