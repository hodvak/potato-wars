#pragma once
#include <SFML/Graphics.hpp>
#include "MapVector.h"

class Weapon : public sf::Drawable
{
public:
    Weapon();
    
    virtual void handleMouseMoved(const MapVector &mousePosition){};
    virtual void handleMousePressed(const MapVector &mousePosition){};
    virtual void update(const sf::Time &deltaTime) = 0;
    [[nodiscard]] bool isAlive() const;
    
protected:
    void die();
    
private:
    bool m_isAlive;
};