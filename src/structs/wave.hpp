#pragma once
#include <vector>
#include <cstdint>
#include <utility>

struct EnemyWave {
    uint32_t p_id = 0;
    std::vector<std::pair<float, int>> p_enemySpawns = {}; // float is time to spawn and int is id
};
