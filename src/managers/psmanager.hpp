
#pragma once
#include <cstdint>

class PSManager
{
private:
    uint64_t m_money = 0;

public:
    PSManager() = default;

    uint64_t GetMoney() const;
    void AddMoney(uint64_t amount);
    void SubMoney(uint64_t amount);
    void SetMoney(uint64_t amount);

    void Init();
};
