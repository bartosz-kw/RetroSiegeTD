#pragma once
#include <array>
#include <cstdint>

#include "tile.hpp"

struct GameMap {
    std::array<std::array<TileDirection, 18>, 18> p_pathDirections = {};
    std::array<std::array<TileType, 18>, 18> p_tileIdMap = {};
    uint16_t p_id = 0;
};
