#pragma once

#include <unordered_map>
#include "src/structs/tower.hpp"

namespace Towers
{
    inline std::unordered_map<int, Tower> g_towerData =
    {
        // damage, position, id, range, attackSpeed, timeToAttack, typeId, tileId, dirty
        {TowerType::Ninja, Tower{1, {-1, -1}, -1, 75.0f, 0.5f, 0, TowerType::Ninja, 0, true}}
    };

    inline Tower GetTowerData(int typeId)
    {
        auto it = g_towerData.find(typeId);
        if (it != g_towerData.end())
        {
            return it->second;
        }
        return Tower{};
    }
}
