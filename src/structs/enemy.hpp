#pragma once
#include <raylib.h>
#include <cstdint>
struct Enemy
{
    Vector2 p_position = {0,0};
    uint32_t p_id = -1;
    uint16_t p_typeId = 0;
    int16_t p_tileId = 0;
    float p_speed = 0.2;
    float p_timeToMove = 0;
    bool p_alive = true;
    bool p_dirty = true;
};
