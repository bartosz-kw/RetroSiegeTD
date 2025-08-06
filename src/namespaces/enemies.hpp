#pragma once

#include <unordered_map>
#include <cassert>
#include "../structs/enemy.hpp"

namespace Enemies
{
    inline std::unordered_map<int, Enemy> g_enemyData =
    {
        // health, position, id, speed, timeToMove, typeId, walked, tileId, alive, dirty
        {EnemyType::BlueSlime, Enemy{10, {-1, -1}, 1, 1.5f, 0.0f, EnemyType::BlueSlime, 0, -1, true, true}}
    };

    inline Enemy GetEnemyData(int typeId)
    {
        auto it = g_enemyData.find(typeId);
        if (it != g_enemyData.end())
        {
            return it->second;
        }
        assert(false && "couldn't find requested data in enemyData");
        return Enemy{};
    }
}
