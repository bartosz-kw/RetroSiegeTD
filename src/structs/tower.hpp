#pragma once
#include <cstdint>
#include <functional>
#include <raylib.h>
enum TowerType
{
    Nothing = 0,
    NinjaLv1 = 1,
    NinjaLv2 = 2,
    NinjaLv3 = 3,
    NinjaLv4 = 4
};
class TowerManager;
class EnemyManager;
class Enemy;
class BulletManager;
class PSManager;
struct Tower
{              
    std::function<void(const float deltaTime,Tower* tower,Enemy* enemy,EnemyManager* mgr_enemy,BulletManager* mgr_bullet,TowerManager* mgr_tower)> 
    p_fightFunction = [](const float deltaTime,Tower* tower,Enemy* enemy,EnemyManager* mgr_enemy,BulletManager* mgr_bullet,TowerManager* mgr_tower){};
    std::function<void(const float deltaTime,Tower* tower,PSManager* mgr_ps)> 
    p_upgradeFunction = [](const float deltaTime,Tower* tower,PSManager* mgr_ps){};
    uint64_t p_price = 0; 
    int64_t p_damage = 1;  
    Vector2 p_position = {0,0};
    float p_range = 30;
    float p_attackSpeed = 1;
    float p_timeToAttack = 0;
    TowerType p_upgradesTo = TowerType::Nothing;
    int32_t p_id = -1;   
    uint16_t p_level = 0;
    int16_t p_typeId = 0;
    int16_t p_tileId = 0;
    bool p_isUpgradeHovered = false;
    bool p_canUpgrade = false;
    bool p_dirty = true;
};