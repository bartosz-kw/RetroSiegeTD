#pragma once

#include <unordered_map>
#include "src/structs/tower.hpp"

namespace Towers
{
    // Map of TowerType id to Tower data
    inline std::unordered_map<int, Tower> towerData = 
    {
        { TowerType::Ninja, Tower{} }
    };

    // Get Tower data by TowerType id
    inline Tower getTowerData(int typeId)
    {
        auto it = towerData.find(typeId);
        if (it != towerData.end())
        {
            return it->second;
        }
        return Tower{};
    }
}
