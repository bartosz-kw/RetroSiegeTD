#pragma once
#include <raylib.h>
#include <cstdint>
struct Enemy
{
    Vector2 p_position = {0,0};
    uint32_t p_id = -1;
    uint16_t p_typeId = 0;
    uint16_t p_tileId = 0;
    bool p_dirty = true;
};
