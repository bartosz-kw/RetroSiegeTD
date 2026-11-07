#pragma once
#include <array>
#include <cstdint>

#include <raylib.h>

#include "../structs/tile.hpp"

namespace Loading {
std::array<std::array<TileDirection, 18>, 18> LoadMapDirections(const char* path);
std::array<std::array<TileType, 18>, 18> LoadTileTypes(const char* path);
} // namespace Loading
