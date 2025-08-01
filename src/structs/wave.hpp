#pragma once
#include <vector>
#include <utility>

struct EnemyWave {
    int p_id;
    std::vector<std::pair<float, int>> p_values;
};
