#pragma once
#include <raylib.h>
#include <cstdint>
#include <functional>
#include <vector>
enum EnemyType
{
    BlueSlime = 1
};
struct Enemy
{
    std::vector<std::pair<float, int32_t>> p_hitCooldowns = {};
    std::function<void(const float deltaTime, Enemy &enemy)>
        p_updateAnimation = [](const float deltaTime, Enemy &enemy) {};
    Rectangle p_sourceRect = {0, 0, 0, 0};
    uint64_t p_moneyDrop = 0;
    int64_t p_health = 10;
    Vector2 p_position = {0, 0};
    uint32_t p_id = -1;
    float p_speed = 1;
    float p_timeToNextFrame = 0.0f;
    float p_timePassed = 0.0f;
    float p_timeToMove = 0.0f;
    float p_hitEffectTime = 0.0f;
    uint16_t p_typeId = 0;
    uint16_t p_walked = 0;
    int16_t p_tileId = 0;
    bool p_alive = true;
    bool p_survived = false;
    bool p_dirty = true;
};
