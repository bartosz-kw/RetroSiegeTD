#include "psmanager.hpp"

uint64_t PSManager::GetMoney() const
{
    return m_money;
}

void PSManager::AddMoney(uint64_t amount)
{
    m_money += amount;
}

void PSManager::SubMoney(uint64_t amount)
{
    if (amount <= m_money)
    {
        m_money -= amount;
    }
}

void PSManager::SetMoney(uint64_t amount)
{
    m_money = amount;
}

void PSManager::Init()
{
    m_money = 0;
}
