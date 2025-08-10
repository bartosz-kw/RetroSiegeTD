#include "psmanager.hpp"
#include <raymath.h>

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
    else
    {
        m_money = 0;
    }
}
void PSManager::SetMoney(uint64_t amount)
{
    m_money = amount;
}
uint64_t PSManager::GetHealth() const
{
    return m_health;
}
void PSManager::AddHealth(uint64_t amount)
{
    m_health = Clamp(m_health + amount, 0.0f , m_maxHealth);
}
void PSManager::SubHealth(uint64_t amount)
{
    if (amount <= m_health)
    {
        m_health -= amount;
    }
    else
    {
        m_health = 0;
    }
}
void PSManager::SetHealth(uint64_t amount)
{
    m_health = amount;
}
bool PSManager::IsAlive() const
{
    return m_health > 0;
}
bool PSManager::CanAfford(uint64_t cost) const
{
    return m_money >= cost;
}
uint64_t PSManager::GetMaxHealth() const
{
    return m_maxHealth;
}
void PSManager::Init()
{
    m_money = 250;
    m_health = 100;
    m_maxHealth = 100;
}
