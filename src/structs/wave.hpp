#pragma once
#include <vector>
#include <utility>

struct EnemyWave {
    int p_id;
    std::vector<std::pair<float, int>> p_enemySpawns; // float is time to spawn and int is id
};
