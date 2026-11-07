#pragma once
#include <cstdint>
#include <utility>

#include "enemy.hpp"

struct EnemyWave {
    std::vector<std::pair<float, EnemyType>> p_enemySpawns = {};
    uint64_t p_moneyReward = 0;
    float p_totalWaveTime = 0.0f;
    uint32_t p_id = 0;
};
