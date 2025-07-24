#pragma once
#include <cstdint>
#include <array>
struct GameMap
{
    uint16_t p_id = 0;
    std::array<std::array<uint16_t, 18>, 18> p_tileIdMap = {};
};
