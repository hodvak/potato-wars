#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "GameMap.h"
#include "MapObject/Character.h"
#include "BombHandler.h"
#include "Weapon/Weapon.h"
#include "Weapon/WeaponCreatorContainer.h"
#include "Camera.h"
#include "Team.h"

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
    
    Team m_teams[PlayerColor::SIZE];
    int m_teamTurnIndex;
    
    void
    updateObjectsInterval(const sf::Time &deltaTime, const sf::Time &interval);

    void updateObjects(sf::Time time);

    void updateCollision();

    void addMovingObject(std::unique_ptr<MovingMapObject> &&object);

    void stopMovingObjects();
    
    void addCharacter(const PlayerColor &color,const MapVector &position);


};