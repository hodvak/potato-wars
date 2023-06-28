#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameMap.h"
#include "Explosion.h"
#include <functional>
class MovingMapObject;

/**
 * a class that handles the bombs in the game.
 * draw the bombs on the map and update the objects according to the bombs
 */
class BombHandler
{
public:
    /**
     * regular constructor
     */
    BombHandler();

    /**
     * add a BOMB to the handler
     * @param bomb the BOMB to add
     */
    void addBomb(const Explosion &bomb);

    /**
     * draw the bombs on the map and update the objects according to the bombs
     * delete the bombs after the update
     * @param map the map to draw on
     * @param objects the objects to update
     */
    void update(GameMap *map,
                std::vector<std::unique_ptr<MovingMapObject>> &objects);

    void setAddFragments(std::function<void(MapVector ,MapVector)> addFragments);
private:
    /**
     * the bombs in the handler
     */
    std::vector<Explosion> m_bombs;
    std::function<void(MapVector ,MapVector)> m_addFragments;
};
