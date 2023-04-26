#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "map.h"
#include "bomb.h"

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
     * add a bomb to the handler
     * @param bomb the bomb to add
     */
    void add_bomb(const Bomb &bomb);

    /**
     * draw the bombs on the map and update the objects according to the bombs
     * delete the bombs after the update
     * @param map the map to draw on
     * @param objects the objects to update
     */
    void update(Map *map,
                std::vector<std::unique_ptr<MovingMapObject>> &objects);

private:
    /**
     * the bombs in the handler
     */
    std::vector<Bomb> m_bombs;
};
