#pragma once
#include <raylib.h>
#include <cstdint>

enum BulletType
{
    Shuliken = 1,
    SharpShuliken = 2,
    Dagger = 3
};

struct Bullet
{
    Vector2 p_position = {0, 0};
    int32_t p_id = -1;
    int32_t p_damage = 1;
    float p_directionAngle = 0;
    float p_rotation = 0.0f;
    float p_spinSpeed = 3.0f;
    float p_speed = 1.0f;
    uint16_t p_typeId = BulletType::Shuliken;
    bool p_pierce = false;
    bool p_alive = true;
};