#pragma once
#include <raylib.h>
#include <cstdint>
#include <array>

std::array<std::array<int16_t, 18>, 18> LoadMapDirections(const char *path);
std::array<std::array<uint16_t, 18>, 18> LoadTileTypes(const char *path);