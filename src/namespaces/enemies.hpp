#pragma once

#include <unordered_map>
#include <cassert>
#include "../structs/enemy.hpp"

namespace Enemies
{
    inline std::unordered_map<int, Enemy> g_enemyData =
    {
        // health, position, id, typeId, walked, tileId, speed, timeToMove, alive, dirty
        {EnemyType::BlueSlime, Enemy{10, {-1, -1}, 1, EnemyType::BlueSlime, 0, -1, 1.5f, 0.0f, true, true}}
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
