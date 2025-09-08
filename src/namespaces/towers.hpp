#pragma once
#include <unordered_map>
#include "../structs/tower.hpp"

namespace Towers
{
    extern std::unordered_map<int, Tower> g_towerData;
    extern std::unordered_map<TowerType, uint16_t> g_towerAmountLimits;

    void InitTowerData();
    Tower GetTowerData(int typeId);
}
