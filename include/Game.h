#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "GameMap.h"
#include "MapObject/Ball.h"
#include "BombHandler.h"


class Game: public sf::Drawable
{
public:
    explicit Game(const std::string &levelName);
    virtual void update(const sf::Time &deltaTime);
    virtual void handleEvent(const sf::Event &event);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
private:
    GameMap m_map;
    std::vector<std::unique_ptr<MovingMapObject>> m_movingObjects;
    BombHandler m_bombHandler;
};