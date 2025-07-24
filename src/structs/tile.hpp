#pragma once
#include <cstdint>
#include <raylib.h>
struct Tile
{
    uint16_t p_id = 0;
    uint16_t p_typeId = 0;
    Vector2 p_position = {0,0};
};