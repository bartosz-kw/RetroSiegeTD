#pragma once
#include <cstdint>
#include <functional>
#include <raylib.h>
enum TowerType
{
    NinjaLv1 = 1,
    NinjaLv2 = 2,
    NinjaLv3 = 3,
    NinjaLv4 = 4
};
class TowerManager;
class EnemyManager;
class Enemy;
class BulletManager;
struct Tower
{              
    std::function<void(float deltaTime,Tower* tower,Enemy* enemy,EnemyManager* mgr_enemy,BulletManager* mgr_bullet,TowerManager* mgr_tower)> 
    p_fightFunction = [](float deltaTime,Tower* tower,Enemy* enemy,EnemyManager* mgr_enemy,BulletManager* mgr_bullet,TowerManager* mgr_tower){};
    std::function<void(float deltaTime,Tower* tower)> p_upgradeFunction = [](float deltaTime,Tower* tower){};
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