#pragma once

#include "MapObject/Crates/Crate.h"
#include <functional>


class CrateDropper
{
public:
    CrateDropper(int mapRange, GameHelperData &gameHelperData);

    ~CrateDropper() = default;

    void dropCrate();

private:
    int m_mapRange;

    GameHelperData &m_gameHelperData;
    
    std::vector<std::function<std::unique_ptr<Crate>(int)>> m_crateCrates;





};
