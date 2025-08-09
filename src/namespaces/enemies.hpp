#pragma once

#include <unordered_map>
#include "../structs/enemy.hpp"

namespace Enemies
{
    extern std::unordered_map<int, Enemy> g_enemyData;

    void InitEnemyData();
    Enemy GetEnemyData(int typeId);
}
