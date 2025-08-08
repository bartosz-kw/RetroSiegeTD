#pragma once

#include <unordered_map>
#include <cassert>
#include "../structs/enemy.hpp"

namespace Enemies
{
    inline std::unordered_map<int, Enemy> g_enemyData = {};

    inline void InitEnemyData()
    {
        g_enemyData.clear();
        
        // Blue Slime
        Enemy blueSlime = {};
        blueSlime.p_moneyDrop = 10;
        blueSlime.p_health = 10;
        blueSlime.p_position = {-1.0f, -1.0f};
        blueSlime.p_id = 1;
        blueSlime.p_speed = 1.5f;
        blueSlime.p_timeToMove = 0.0f;
        blueSlime.p_typeId = EnemyType::BlueSlime;
        blueSlime.p_walked = 0;
        blueSlime.p_tileId = -1;
        blueSlime.p_alive = true;
        blueSlime.p_dirty = true;
        
        g_enemyData[EnemyType::BlueSlime] = blueSlime;
    }

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
