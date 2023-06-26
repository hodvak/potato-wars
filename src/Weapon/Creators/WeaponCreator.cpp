#include "Weapon/Creators/WeaponCreator.h"

WeaponCreator::WeaponCreator(int amount,
                             GameHelperData &gameHelperData) :
        m_amount(amount),
        m_gameHelperData(gameHelperData)
{
}

std::unique_ptr<Weapon> WeaponCreator::createWeapon(Character &character)
{
    if (m_amount == 0)
    {
        return nullptr;
    }
    else if (m_amount > 0)
    {
        m_amount--;
        return createWeaponImpl(character);
    }
    else
    {
        return createWeaponImpl(character);
    }
}

int WeaponCreator::getAmount() const
{
    return m_amount;
}

void WeaponCreator::addAmount(int amount)
{
    if (m_amount == -1)
    {
        return;
    }
    else if (amount == -1)
    {
        m_amount = -1;
        return;
    }
    m_amount += amount;
}

GameHelperData &WeaponCreator::getGameHelperData() const
{
    return m_gameHelperData;
}
