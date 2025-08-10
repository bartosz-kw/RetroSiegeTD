
#pragma once
#include <cstdint>

class PSManager
{
private:
    uint64_t m_money = 0;
    uint64_t m_health = 0;
    uint64_t m_maxHealth = 0;
public:
    PSManager() = default;

    // money
    uint64_t GetMoney() const;
    void AddMoney(uint64_t amount);
    void SubMoney(uint64_t amount);
    void SetMoney(uint64_t amount);
    bool CanAfford(uint64_t cost) const;
    // health
    uint64_t GetHealth() const;
    uint64_t GetMaxHealth() const;
    void AddHealth(uint64_t amount);
    void SubHealth(uint64_t amount);
    void SetHealth(uint64_t amount);
    bool IsAlive() const;

    void Init();
};
