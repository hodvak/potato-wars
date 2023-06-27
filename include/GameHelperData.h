#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "GameMap.h"
#include "BombHandler.h"
#include "SoundPlayer.h"
/**
 * this class represent the data that every object in the game need to live
 * every game will hold one instance of this class
 * the object in the game will get a reference to this class
 */
class GameHelperData
{
public:
    /**
     * regular constructor
     * @param window the window of the game
     * @param map the map of the game
     * @param bombHandler the bomb handler of the game
     */
    GameHelperData(
            GameMap &map,
            BombHandler &bombHandler,
            SoundPlayer &soundPlayer,
            sf::RenderWindow *window = nullptr,
            sf::Time deltaTime = sf::Time::Zero
    );
    /**
     * setter for the add object function
     */
     void setAddObjectFunc(const std::function<void (std::unique_ptr<MovingMapObject> &&)> &func);

    /**
     * get the delta time of the game
     * the delta time can not be changed, so return const reference
     * @return the delta time of the game
     */
    [[nodiscard]] const sf::Time &getDeltaTime() const;

    /**
     * get the position of the mouse in the window
     */
    [[nodiscard]] sf::Vector2f getMousePositionInWindow() const;

    /**
     * get the position of the mouse in the map
     */
    [[nodiscard]] MapVector getMousePositionInMap() const;

    /**
     * get the size of the window
     */
    [[nodiscard]] sf::Vector2f getWindowSize() const;
    
    void addMapObject(std::unique_ptr<MovingMapObject> &&mapObject);


    /**
     * get the map of the game
     * map can be changed, so return reference
     * @return the map of the game, may be nullptr if game isn't started
     * yet 
     */
    [[nodiscard]] GameMap &getMap() const;

    /**
     * get the bomb handler of the game
     * bomb handler can be changed(adding bombs), so return reference
     * @return the bomb handler of the game
     */
    [[nodiscard]] BombHandler &getBombHandler() const;

    /**
     * set the delta time of the game
     * @param deltaTime the delta time of the game
     */
    void setDeltaTime(const sf::Time &deltaTime);

    /**
     * set the window of the game (may only be called once, when the game starts)
     * @param window the window of the game
     */
    void setWindow(const sf::RenderWindow &window);

    const sf::View &getView() const;

private:
    sf::Time m_deltaTime;
    /**
     * the window may only used for getting the mouse position (in 2 ways)
     * and getting the window size
     */
    const sf::RenderWindow *m_window;
    GameMap &m_map;
    BombHandler &m_bombHandler;
    SoundPlayer &m_soundPlayer;
    std::function<void (std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
};