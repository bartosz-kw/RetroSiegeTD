#pragma once
#include <raylib.h>
#include <functional>
#include <cstdint>

class BulletManager;
enum BulletType
{
    Shuliken = 1,
    SharpShuliken = 2,
    Dagger = 3,
    Slash = 4
};

struct Bullet
{
    std::function<void(const float deltaTime, Bullet& bullet)>
        p_updateAnimation = [](const float deltaTime, Bullet& bullet) {};
    Rectangle p_sourceRect = {0, 0, 0, 0};
    Vector2 p_position = {0, 0};
    int32_t p_id = -1;
    int32_t p_damage = 1;
    float p_timeToNextFrame = 0.0f;
    float p_timePassed = 0.0f;
    float p_directionAngle = 0;
    float p_rotation = 0.0f;
    float p_spinSpeed = 3.0f;
    float p_speed = 1.0f;
    uint16_t p_typeId = BulletType::Shuliken;
    bool p_pierce = false;
    bool p_alive = true;
};