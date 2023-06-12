#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "GameMap.h"
#include "MapObject/Character.h"
#include "BombHandler.h"
#include "Weapon/Weapon.h"
#include "Camera.h"

//todo: add documentation

class Game: public sf::Drawable
{
public:
    explicit Game(const std::string &levelName);
    virtual void update(const sf::Time &deltaTime);
    void handleMouseMoved(const MapVector &mousePosition);
    void handleMousePressed(const MapVector &mousePosition);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    
private:
    GameMap m_map;
    std::vector<std::unique_ptr<MovingMapObject>> m_movingObjects;
    BombHandler m_bombHandler;
    Camera m_camera;

    std::unique_ptr<Weapon> m_weapon;

    std::vector<Character *> m_characters; // todo: make player or 3 vectors
    void
    updateObjectsInterval(const sf::Time &deltaTime, const sf::Time &interval);

    void updateObjects(sf::Time time);

    void updateCollision();

    void addMovingObject(std::unique_ptr<MovingMapObject> &&object);

    void stopMovingObjects();


};