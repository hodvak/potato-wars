#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "GameMap.h"
#include "MapObject/Character.h"
#include "BombHandler.h"
#include "Weapon/Weapon.h"
#include "Weapon/WeaponCreatorContainer.h"
#include "Camera.h"
#include "Team.h"
#include "CrateDropper.h"

/**
 * a class that handle the game (the main class in the project)
 */
class Game: public sf::Drawable
{
public:
    /**
     * regular constructor
     * @param levelName the name of the level to load
     */
    explicit Game(const std::string &levelName);
    
    /**
     * update the game
     * @param deltaTime the time passed since the last update
     */
    virtual void update(const sf::Time &deltaTime);
    
    /**
     * handle the mouse moved event
     * @param mousePosition the mouse position
     */
    void handleMouseMoved(const MapVector &mousePosition);
    
    /**
     * handle the mouse pressed event
     * @param mousePosition the mouse position
     */
    void handleMousePressed(const MapVector &mousePosition);

    /**
     * draw the game on the target
     * @param target the target to draw on
     * @param states the states to draw with
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    
private:
    
    /**
     * the map of the game
     */
    GameMap m_map;
    
    /**
     * all the objects in the game that can move
     */
    std::vector<std::unique_ptr<MovingMapObject>> m_movingObjects;
    
    /**
     * explosion handler of the game
     */
    BombHandler m_bombHandler;
    
    /**
     * camera of the game
     */
    Camera m_camera;
    
    /**
     * the team that play the game (all team exists in every game, team that 
     * doesn't play is empty)
     */
    Team m_teams[PlayerColor::SIZE];
    
    /**
     * the index of the team that play the game
     */
    int m_teamTurnIndex;
    
    /**
     * make small updates to the objects in the game
     * until the time passed is equal than the interval
     * @param deltaTime the sum of all small updates
     * @param interval the time for small update
     */
    void
    updateObjectsInterval(const sf::Time &deltaTime, const sf::Time &interval);

    /**
     * update the objects in the game
     * @param deltaTime the time passed since the last update
     */
    void updateObjects(const sf::Time &deltaTime);

    /**
     * update the collision of the objects in the game
     */
    void updateCollision();

    /**
     * add a moving object to the game
     * @param object the object to add
     */
    void addMovingObject(std::unique_ptr<MovingMapObject> &&object);

    /**
     * stop the objects in the game if all need to stop
     */
    void stopMovingObjects();
    
    /**
     * add a character to the game
     */
    void addCharacter(const PlayerColor &color,const MapVector &position);
    /**
     * if all object stopped moving
     */
    bool m_allStopped;
    /**
     * the crate dropper
     */
    CrateDropper m_crateDropper;
};