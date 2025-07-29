#pragma once
#include <raylib.h>
#include <cstdint>
enum EnemyType
{
    BlueSlime = 1
};
struct Enemy
{
    int64_t p_health = 10;
    Vector2 p_position = {0,0};
    uint32_t p_id = -1;
    uint16_t p_typeId = 0;
    uint16_t p_walked = 0;
    int16_t p_tileId = 0;
    float p_speed = 1;
    float p_timeToMove = 0;
    bool p_alive = true;
    bool p_dirty = true;
};
