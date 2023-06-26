#pragma once
#include <SFML/Graphics.hpp>
#include "MapVector.h"
#include "GameHelperData.h"


/**
 * an abstract class that represents a weapon in the game
 */
class Weapon : public sf::Drawable
{
public:
    /**
     * regular constructor
     */
    Weapon(GameHelperData &gameHelperData);
    
    /**
     * handle the mouse moved event
     * @param mousePosition the mouse position
     */
    virtual void handleMouseMoved(const MapVector &mousePosition){};
    
    /**
     * handle the mouse pressed event
     * @param mousePosition the mouse position
     */
    virtual void handleMousePressed(const MapVector &mousePosition){};
    
    /**
     * update the weapon
     * @param deltaTime the time passed since the last update
     */
    virtual void update(const sf::Time &deltaTime) = 0;
    
    /**
     * check if the weapon is alive
     * @return 
     */
    [[nodiscard]] bool isAlive() const;

    [[nodiscard]] virtual bool turnEnder() const;
    
    [[nodiscard]] GameHelperData &getGameHelperData() const;

protected:
    /**
     * kill the weapon
     */
    void die();
    
private:
    
    /**
     * is the weapon alive
     */
    bool m_isAlive;
    
    GameHelperData &m_gameHelperData;
};