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
    
    static const std::map<int, std::function<std::unique_ptr<Crate> (int x,const CrateDropper &crateDropper)>>
            m_crateCrates;

    static std::unique_ptr<Crate>
    rifleCreator(int x, const CrateDropper &crateDropper);

    static std::unique_ptr<Crate> rockCreator(int x, const CrateDropper &crateDropper);

    static std::unique_ptr<Crate> bombCreator(int x, const CrateDropper &crateDropper);

    static std::unique_ptr<Crate>
    healthCreator(int x,const CrateDropper &crateDropper);
};
