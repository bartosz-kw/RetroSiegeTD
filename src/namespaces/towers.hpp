#pragma once

#include <unordered_map>
#include <cassert>
#include "src/structs/tower.hpp"

namespace Towers
{
    inline std::unordered_map<int, Tower> g_towerData = {};

    inline void InitTowerData()
    {
        g_towerData.clear();
        
        // ninja Lv 1
        Tower ninja1Tower = {};
        ninja1Tower.p_price = 25;
        ninja1Tower.p_damage = 1;
        ninja1Tower.p_position = {-1.0f, -1.0f};
        ninja1Tower.p_range = 75.0f;
        ninja1Tower.p_attackSpeed = 0.5f;
        ninja1Tower.p_timeToAttack = 0.0f;
        ninja1Tower.p_id = -1;
        ninja1Tower.p_level = 0;
        ninja1Tower.p_typeId = TowerType::Ninja;
        ninja1Tower.p_tileId = 0;
        ninja1Tower.p_dirty = true;
        
        g_towerData[TowerType::Ninja] = ninja1Tower;
    }

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
