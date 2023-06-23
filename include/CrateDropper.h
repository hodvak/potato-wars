#pragma once

#include "MapObject/Crates/Crate.h"
#include <functional>


class CrateDropper
{
public:
    CrateDropper(int mapRange, const std::function<void(
            std::unique_ptr<MovingMapObject> &&)> &addMapObjectFunc,
                 const GameMap &map, BombHandler &bombHandler);

    ~CrateDropper() = default;

    void dropCrate();

private:
    int m_mapRange;
    const GameMap &m_map;
    BombHandler &m_bombHandler;
    std::function<void(std::unique_ptr<MovingMapObject> &&)> m_addMapObjectFunc;
    static const std::map<int, std::function<std::unique_ptr<Crate> (int x,const CrateDropper &crateDropper)>>
            m_crateCrates;

    static std::unique_ptr<Crate>
    rifleCreator(int x, const CrateDropper &crateDropper);

    static std::unique_ptr<Crate> rockCreator(int x, const CrateDropper &crateDropper);

    static std::unique_ptr<Crate> bombCreator(int x, const CrateDropper &crateDropper);

    static std::unique_ptr<Crate>
    healthCreator(int x,const CrateDropper &crateDropper);
};
