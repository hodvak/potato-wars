#pragma once

#include "MapObject/Crates/Crate.h"
#include <functional>

/**
 * a class that drops crates on the map
 */
class CrateDropper
{
public:
    CrateDropper(int mapRange, GameHelperData &gameHelperData);

    ~CrateDropper() = default;

    void dropCrate();

private:
    // the range of the map to drop the crates
    int m_mapRange;
    // the game helper data
    GameHelperData &m_gameHelperData;
    //vector of functions that create crates
    std::vector<std::function<std::unique_ptr<Crate>(int)>> m_crateCrates;





};
