#pragma once
#include <vector>
#include <cstdint>
#include <utility>

struct EnemyWave {
    std::vector<std::pair<float, int>> p_enemySpawns = {}; // float is time to spawn and int is id
    uint64_t p_moneyReward = 0;
    float p_totalWaveTime = 0.0f;
    uint32_t p_id = 0;
};
