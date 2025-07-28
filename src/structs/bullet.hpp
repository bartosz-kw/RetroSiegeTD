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
    Vector2 p_position = {0, 0};
    int32_t p_damage = 1;
    float p_speed = 0.0f;
    float p_radius = 4.0f;
    uint16_t p_typeId = BulletType::Shuliken;
};