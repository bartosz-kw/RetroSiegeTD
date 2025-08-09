#include "towers.hpp"
#include "bullets.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/bulletmanager.hpp"
#include <unordered_map>
#include <cassert>
#include <cmath>

namespace Towers
{
    std::unordered_map<int, Tower> g_towerData = {};

    void InitTowerData()
    {
        g_towerData.clear();

        #pragma region NinjaLv1
        // ninja Lv 1
        Tower ninja1Tower = {};
        ninja1Tower.p_fightFunction = [](float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager* mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            // make bullet
            Bullet bullet = Bullets::GetBulletData(BulletType::Shuliken);
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        ninja1Tower.p_upgradeFunction = [](float deltaTime, Tower *tower) 
        {
            PrintDebug("Update Func");
        };
        ninja1Tower.p_price = 25;
        ninja1Tower.p_damage = 1;
        ninja1Tower.p_position = {-1.0f, -1.0f};
        ninja1Tower.p_range = 75.0f;
        ninja1Tower.p_attackSpeed = 0.5f;
        ninja1Tower.p_timeToAttack = 0.0f;
        ninja1Tower.p_id = -1;
        ninja1Tower.p_level = 0;
        ninja1Tower.p_typeId = TowerType::NinjaLv1;
        ninja1Tower.p_tileId = 0;
        ninja1Tower.p_dirty = true;

        g_towerData[TowerType::NinjaLv1] = ninja1Tower;
        #pragma endregion

        #pragma region NinjaLv2
        // ninja Lv 2
        Tower ninja2Tower = {};
        ninja2Tower.p_fightFunction = [](float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager* mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            // make bullet
            Bullet bullet = Bullets::GetBulletData(BulletType::Shuliken);
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        ninja2Tower.p_upgradeFunction = [](float deltaTime, Tower *tower) 
        {
            PrintDebug("Update Func");
        };
        ninja2Tower.p_price = 50;
        ninja2Tower.p_damage = 2;
        ninja2Tower.p_position = {-1.0f, -1.0f};
        ninja2Tower.p_range = 85.0f;
        ninja2Tower.p_attackSpeed = 0.4f;
        ninja2Tower.p_timeToAttack = 0.0f;
        ninja2Tower.p_id = -1;
        ninja2Tower.p_level = 0;
        ninja2Tower.p_typeId = TowerType::NinjaLv2;
        ninja2Tower.p_tileId = 0;
        ninja2Tower.p_dirty = true;

        g_towerData[TowerType::NinjaLv2] = ninja2Tower;
        #pragma endregion

        #pragma region NinjaLv3
        // ninja Lv 3
        Tower ninja3Tower = {};
        ninja3Tower.p_fightFunction = [](float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager* mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            // make bullet
            Bullet bullet = Bullets::GetBulletData(BulletType::Shuliken);
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        ninja3Tower.p_upgradeFunction = [](float deltaTime, Tower *tower) 
        {
            PrintDebug("Update Func");
        };
        ninja3Tower.p_price = 75;
        ninja3Tower.p_damage = 3;
        ninja3Tower.p_position = {-1.0f, -1.0f};
        ninja3Tower.p_range = 95.0f;
        ninja3Tower.p_attackSpeed = 0.3f;
        ninja3Tower.p_timeToAttack = 0.0f;
        ninja3Tower.p_id = -1;
        ninja3Tower.p_level = 0;
        ninja3Tower.p_typeId = TowerType::NinjaLv3;
        ninja3Tower.p_tileId = 0;
        ninja3Tower.p_dirty = true;

        g_towerData[TowerType::NinjaLv3] = ninja3Tower;
        #pragma endregion

        #pragma region NinjaLv4
        // ninja Lv 4
        Tower ninja4Tower = {};
        ninja4Tower.p_fightFunction = [](float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager* mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            // make bullet
            Bullet bullet = Bullets::GetBulletData(BulletType::Shuliken);
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        ninja4Tower.p_upgradeFunction = [](float deltaTime, Tower *tower) 
        {
            PrintDebug("Update Func");
        };
        ninja4Tower.p_price = 100;
        ninja4Tower.p_damage = 4;
        ninja4Tower.p_position = {-1.0f, -1.0f};
        ninja4Tower.p_range = 105.0f;
        ninja4Tower.p_attackSpeed = 0.25f;
        ninja4Tower.p_timeToAttack = 0.0f;
        ninja4Tower.p_id = -1;
        ninja4Tower.p_level = 0;
        ninja4Tower.p_typeId = TowerType::NinjaLv4;
        ninja4Tower.p_tileId = 0;
        ninja4Tower.p_dirty = true;

        g_towerData[TowerType::NinjaLv4] = ninja4Tower;
        #pragma endregion
    }

    Tower GetTowerData(int typeId)
    {
        auto it = g_towerData.find(typeId);
        if (it != g_towerData.end())
        {
            return it->second;
        }
        assert(false && "couldn't find requested data in towerData");
        return Tower{};
    }
}
