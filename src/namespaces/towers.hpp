#pragma once
#include <unordered_map>
#include "../structs/tower.hpp"

namespace Towers
{
    extern std::unordered_map<int, Tower> g_towerData;

    void InitTowerData();
    Tower GetTowerData(int typeId);
}
