#pragma once
#include <raylib.h>
#include <cstdint>

enum BulletType
{
    Shuliken = 1
};

struct Bullet
{
    int32_t p_id = -1;
    int32_t p_damage = 1;
    Vector2 p_position = {0, 0};
    float p_angle = 0;
    float p_speed = 1.0f;
    float p_radius = 3.0f;
    uint16_t p_typeId = BulletType::Shuliken;
    bool p_alive = true;
};