#pragma once
#include <cstdint>
#include <array>
struct GameMap
{
    std::array<std::array<int16_t, 18>, 18> p_pathDirections = {}; // -1 = no path
    std::array<std::array<uint16_t, 18>, 18> p_tileIdMap = {};
    uint16_t p_id = 0;
};
