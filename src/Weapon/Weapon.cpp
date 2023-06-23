#include "Weapon/Weapon.h"

Weapon::Weapon():
    m_isAlive(true),m_endsTurn(false)
{

}

void Weapon::die()
{
    m_isAlive = false;
}

bool Weapon::isAlive() const
{
    return m_isAlive;
}

bool Weapon::turnEndded() const
{
    return m_endsTurn;
}

void Weapon::endTurn()
{
    m_endsTurn = true;
}


