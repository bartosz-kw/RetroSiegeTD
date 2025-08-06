#pragma once

#include <unordered_map>
#include <cassert>
#include "src/structs/tower.hpp"

namespace Towers
{
    inline std::unordered_map<int, Tower> g_towerData =
    {
            // damage, position, range, attackSpeed, timeToAttack, id, level, typeId, tileId, dirty
            {TowerType::Ninja, Tower{1, {-1, -1}, 75.0f, 0.5f, 0, -1, 0, TowerType::Ninja, 0, true}}
    };

    inline Tower GetTowerData(int typeId)
    {
        auto it = g_towerData.find(typeId);
        if (it != g_towerData.end())
        {
            return it->second;
        }
        assert(false && "couldn't find requested data in towerData");
        return Tower{};
    }
}
