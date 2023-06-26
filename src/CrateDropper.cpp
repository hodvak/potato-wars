#include "CrateDropper.h"
#include "MapObject/Crates/WeaponCrate.h"
#include "MapObject/Crates/HealthCrate.h"
#include "MapObject/Crates/Crate.h"
#include "Weapon/Creators/RifleWeaponCreator.h"
#include "Weapon/Creators/StoneThrowCreator.h"
#include "Weapon/Creators/BombThrowCreator.h"


CrateDropper::CrateDropper(int mapRange, GameHelperData &gameHelperData) :
        m_mapRange(mapRange),
        m_gameHelperData(gameHelperData)
{

}

// todo: IDK just think about it must change
std::unique_ptr<Crate>
CrateDropper::rifleCreator(int x, const CrateDropper &crateDropper)
{
    std::unique_ptr<RifleWeaponCreator> rifle = std::make_unique<RifleWeaponCreator>(
            1,
            crateDropper.m_gameHelperData
    );
    MapVector pos = MapVector{(float) x, 0};
    std::unique_ptr<Crate> crate =
            std::make_unique<WeaponCrate>(pos,
                                          std::move(rifle),
                                          crateDropper.m_gameHelperData);
    return crate;
}

std::unique_ptr<Crate>
CrateDropper::rockCreator(int x, const CrateDropper &crateDropper)
{
    std::unique_ptr<StoneThrowCreator> rock = std::make_unique<StoneThrowCreator>(
            1,
            crateDropper.m_gameHelperData
    );
    return std::unique_ptr<Crate>(std::make_unique<WeaponCrate>(
            MapVector{(float) x, 0},
            std::move(rock),
            crateDropper.m_gameHelperData)
    );

}

std::unique_ptr<Crate>
CrateDropper::bombCreator(int x, const CrateDropper &crateDropper)
{
    std::unique_ptr<BombThrowCreator> bomb = std::make_unique<BombThrowCreator>(
            1,
            crateDropper.m_gameHelperData
    );
    return std::make_unique<WeaponCrate>(
            MapVector{float(x), 0},
            std::move(bomb),
            crateDropper.m_gameHelperData
    );
}

std::unique_ptr<Crate>
CrateDropper::healthCreator(int x, const CrateDropper &crateDropper)
{
    return std::make_unique<HealthCrate>(
            MapVector{float(x), 0},
            crateDropper.m_gameHelperData
    );
}

const std::map<int, std::function<std::unique_ptr<Crate>(int x,
                                                         const CrateDropper &crateDropper)>> CrateDropper::m_crateCrates = {
        {0, [](int x,
               const CrateDropper &crateDropper) -> std::unique_ptr<Crate>
            {
                return rifleCreator(x, crateDropper);
            }},
        {1, [](int x,
               const CrateDropper &crateDropper) -> std::unique_ptr<Crate>
            {
                return rockCreator(x, crateDropper);
            }},
        {2, [](int x,
               const CrateDropper &crateDropper) -> std::unique_ptr<Crate>
            {
                return bombCreator(x, crateDropper);
            }},
        {3, [](int x,
               const CrateDropper &crateDropper) -> std::unique_ptr<Crate>
            {
                std::unique_ptr<Crate> crate = healthCreator(x, crateDropper);
                return std::move(crate);
            }}
};

void CrateDropper::dropCrate()
{

    int crateType = rand() % m_crateCrates.size();
    int x = rand() % m_mapRange;
    std::unique_ptr<Crate> crateHealth = std::make_unique<HealthCrate>(
            MapVector{float(x), 0}, m_gameHelperData);

    std::unique_ptr<Crate> crate1 = m_crateCrates.at(crateType)(x, *this);
    m_gameHelperData.addMapObject(std::move(crate1));
}
