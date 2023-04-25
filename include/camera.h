#include "moving_map_object.h"
#include <SFML/Graphics.hpp>
class Camera
{
public:
    Camera();
    void setToFollow(MovingMapObject *object);
    void update (sf::RenderWindow *window);
private:
    MovingMapObject *m_object = nullptr;
    sf::View m_view;

};