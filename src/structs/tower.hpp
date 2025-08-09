#pragma once
#include <cstdint>
#include <functional>
#include <raylib.h>
enum TowerType
{
    Ninja = 1
};
class EnemyManager;
class BulletManager;
struct Tower
{              
    std::function<void(float deltaTime,Tower& tower,EnemyManager* mgr_enemy,BulletManager* mgr_bullet)> 
    p_fightFunction = [](float deltaTime,Tower& tower,EnemyManager* mgr_enemy,BulletManager* mgr_bullet){};
    std::function<void(float deltaTime,Tower& tower)> p_upgradeFunction = [](float deltaTime,Tower& tower){};
    uint64_t p_price = 0;
    int64_t p_damage = 1;  
    Vector2 p_position = {0,0};
    float p_range = 30;
    float p_attackSpeed = 1;
    float p_timeToAttack = 0;
    int32_t p_id = -1;   
    uint16_t p_level = 0;
    int16_t p_typeId = 0;
    int16_t p_tileId = 0;
    bool p_dirty = true;
};