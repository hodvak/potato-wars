#include "CrateDropper.h"
#include "MapObject/Crates/WeaponCrate.h"
#include "MapObject/Crates/HealthCrate.h"
#include "MapObject/Crates/Crate.h"
#include "Weapon/Creators/RifleWeaponCreator.h"
#include "Weapon/Creators/StoneThrowCreator.h"
#include "Weapon/Creators/BombThrowCreator.h"
#include "Weapon/Creators/MinigunWeaponCreator.h"
#include "Weapon/Creators/ShotgunWeaponCreator.h"


CrateDropper::CrateDropper(int mapRange, GameHelperData &gameHelperData) :
        m_mapRange(mapRange),
        m_gameHelperData(gameHelperData)
{

    m_crateCrates = {
            [&](int mapRange)
            {
                return std::make_unique<WeaponCrate>(
                        MapVector{(float) mapRange, 0},
                        std::make_unique<RifleWeaponCreator>(
                                1,
                                m_gameHelperData
                        ),
                        m_gameHelperData
                );
            },
            [&](int mapRange)
            {
                return std::make_unique<WeaponCrate>(
                        MapVector{(float) mapRange, 0},
                        std::make_unique<StoneThrowCreator>(
                                1,
                                m_gameHelperData
                        ),
                        m_gameHelperData
                );
            },
            [&](int mapRange)
            {
                return std::make_unique<WeaponCrate>(
                        MapVector{(float) mapRange, 0},
                        std::make_unique<BombThrowCreator>(
                                1,
                                m_gameHelperData
                        ),
                        m_gameHelperData
                );
            },
            [&](int mapRange)
            {
                return std::make_unique<WeaponCrate>(
                        MapVector{(float) mapRange, 0},
                        std::make_unique<MinigunWeaponCreator>(
                                1,
                                m_gameHelperData
                        ),
                        m_gameHelperData
                );
            },
            [&](int mapRange)
            {
                return std::make_unique<WeaponCrate>(
                        MapVector{(float) mapRange, 0},
                        std::make_unique<ShotgunWeaponCreator>(
                                1,
                                m_gameHelperData
                        ),
                        m_gameHelperData
                );
            },
            [&](int mapRange)
            {
                return std::make_unique<HealthCrate>(
                        MapVector{(float) mapRange, 0},
                        m_gameHelperData
                );
            }
    };

}

void CrateDropper::dropCrate()
{

    int crateType = rand() % m_crateCrates.size();
    int x = rand() % m_mapRange;

    m_gameHelperData.addMapObject(std::move(m_crateCrates[crateType](x)));
}
