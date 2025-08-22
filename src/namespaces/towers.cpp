#include "towers.hpp"
#include "bullets.hpp"
#include "basics.hpp"
#include "../utility/debugUtil.hpp"
#include "../utility/mathUtil.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/psmanager.hpp"
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
        ninja1Tower.p_fightFunction = [](float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::Shuliken);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        ninja1Tower.p_sourceRect = {0, 0, 15, 15};
        ninja1Tower.p_price = 25;
        ninja1Tower.p_damage = 1;
        ninja1Tower.p_position = {-1.0f, -1.0f};
        ninja1Tower.p_range = 75.0f;
        ninja1Tower.p_attackSpeed = 0.5f;
        ninja1Tower.p_timeToAttack = 0.0f;
        ninja1Tower.p_timeToNextFrame = 0.0f;
        ninja1Tower.p_timePassed = 0.0f;
        ninja1Tower.p_upgradesTo = TowerType::NinjaLv2;
        ninja1Tower.p_id = -1;
        ninja1Tower.p_level = 1;
        ninja1Tower.p_frameOffset = 0;
        ninja1Tower.p_frameAmount = 0;
        ninja1Tower.p_typeId = TowerType::NinjaLv1;
        ninja1Tower.p_tileId = 0;
        ninja1Tower.p_isUpgradeHovered = false;
        ninja1Tower.p_canUpgrade = true;
        ninja1Tower.p_dirty = true;

        g_towerData[TowerType::NinjaLv1] = ninja1Tower;
#pragma endregion

#pragma region NinjaLv2
        // ninja Lv 2
        Tower ninja2Tower = {};
        ninja2Tower.p_fightFunction = [](float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::SharpShuliken);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        ninja2Tower.p_sourceRect = {0, 0, 15, 15};
        ninja2Tower.p_price = 55;
        ninja2Tower.p_damage = 2;
        ninja2Tower.p_position = {-1.0f, -1.0f};
        ninja2Tower.p_range = 75.0f;
        ninja2Tower.p_attackSpeed = 0.5f;
        ninja2Tower.p_timeToAttack = 0.0f;
        ninja2Tower.p_timeToNextFrame = 0.0f;
        ninja2Tower.p_timePassed = 0.0f;
        ninja2Tower.p_upgradesTo = TowerType::NinjaLv3;
        ninja2Tower.p_id = -1;
        ninja2Tower.p_level = 2;
        ninja2Tower.p_frameOffset = 0;
        ninja2Tower.p_frameAmount = 0;
        ninja2Tower.p_typeId = TowerType::NinjaLv2;
        ninja2Tower.p_tileId = 0;
        ninja2Tower.p_isUpgradeHovered = false;
        ninja2Tower.p_canUpgrade = true;
        ninja2Tower.p_dirty = true;

        g_towerData[TowerType::NinjaLv2] = ninja2Tower;
#pragma endregion

#pragma region NinjaLv3
        // ninja Lv 3
        Tower ninja3Tower = {};
        ninja3Tower.p_fightFunction = [](float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::SharpShuliken);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        ninja3Tower.p_sourceRect = {0, 0, 15, 15};
        ninja3Tower.p_price = 125;
        ninja3Tower.p_damage = 2;
        ninja3Tower.p_position = {-1.0f, -1.0f};
        ninja3Tower.p_range = 80.0f;
        ninja3Tower.p_attackSpeed = 0.25f;
        ninja3Tower.p_timeToAttack = 0.0f;
        ninja3Tower.p_timeToNextFrame = 0.0f;
        ninja3Tower.p_timePassed = 0.0f;
        ninja3Tower.p_upgradesTo = TowerType::NinjaLv4;
        ninja3Tower.p_id = -1;
        ninja3Tower.p_level = 3;
        ninja3Tower.p_frameOffset = 0;
        ninja3Tower.p_frameAmount = 0;
        ninja3Tower.p_typeId = TowerType::NinjaLv3;
        ninja3Tower.p_tileId = 0;
        ninja3Tower.p_isUpgradeHovered = false;
        ninja3Tower.p_canUpgrade = true;
        ninja3Tower.p_dirty = true;

        g_towerData[TowerType::NinjaLv3] = ninja3Tower;
#pragma endregion

#pragma region NinjaLv4

        // ninja Lv 4
        Tower ninja4Tower = {};
        ninja4Tower.p_fightFunction = [](const float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::Dagger);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = RadiansToDegrees(angle);
            bullet.p_position = bulletPos;
            mgr_bullet->AddBullet(bullet);
        };
        ninja4Tower.p_sourceRect = {0, 0, 15, 15};
        ninja4Tower.p_price = 350;
        ninja4Tower.p_damage = 5;
        ninja4Tower.p_position = {-1.0f, -1.0f};
        ninja4Tower.p_range = 90.0f;
        ninja4Tower.p_attackSpeed = 0.25f;
        ninja4Tower.p_timeToAttack = 0.0f;
        ninja4Tower.p_timeToNextFrame = 0.0f;
        ninja4Tower.p_timePassed = 0.0f;
        ninja4Tower.p_upgradesTo = TowerType::Nothing;
        ninja4Tower.p_id = -1;
        ninja4Tower.p_level = 4;
        ninja4Tower.p_frameOffset = 0;
        ninja4Tower.p_frameAmount = 0;
        ninja4Tower.p_typeId = TowerType::NinjaLv4;
        ninja4Tower.p_tileId = 0;
        ninja4Tower.p_isUpgradeHovered = false;
        ninja4Tower.p_canUpgrade = false;
        ninja4Tower.p_dirty = true;

        g_towerData[TowerType::NinjaLv4] = ninja4Tower;
#pragma endregion

#pragma region KnightLv1
        // knight Lv 1
        Tower knight1Tower = {};
        knight1Tower.p_fightFunction = [](float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::Slash);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = RadiansToDegrees(angle);
            bullet.p_position = enemyPos;
            mgr_bullet->AddBullet(bullet);
        };
        knight1Tower.p_sourceRect = {0, 0, 15, 15};
        knight1Tower.p_price = 50;
        knight1Tower.p_damage = 3;
        knight1Tower.p_position = {-1.0f, -1.0f};
        knight1Tower.p_range = 25.0f;
        knight1Tower.p_attackSpeed = 2.0f;
        knight1Tower.p_timeToAttack = 0.0f;
        knight1Tower.p_timeToNextFrame = 0.0f;
        knight1Tower.p_timePassed = 0.0f;
        knight1Tower.p_upgradesTo = TowerType::KnightLv2;
        knight1Tower.p_id = -1;
        knight1Tower.p_level = 1;
        knight1Tower.p_frameOffset = 0;
        knight1Tower.p_frameAmount = 0;
        knight1Tower.p_typeId = TowerType::KnightLv1;
        knight1Tower.p_tileId = 0;
        knight1Tower.p_isUpgradeHovered = false;
        knight1Tower.p_canUpgrade = true;
        knight1Tower.p_dirty = true;

        g_towerData[TowerType::KnightLv1] = knight1Tower;
#pragma endregion

#pragma region KnightLv2
        // knight Lv 2
        Tower knight2Tower = {};
        knight2Tower.p_fightFunction = [](float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::Slash);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = RadiansToDegrees(angle);
            bullet.p_position = enemyPos;
            mgr_bullet->AddBullet(bullet);
        };
        knight2Tower.p_sourceRect = {0, 0, 15, 15};
        knight2Tower.p_price = 75;
        knight2Tower.p_damage = 3;
        knight2Tower.p_position = {-1.0f, -1.0f};
        knight2Tower.p_range = 40.0f;
        knight2Tower.p_attackSpeed = 1.5f;
        knight2Tower.p_timeToAttack = 0.0f;
        knight2Tower.p_timeToNextFrame = 0.0f;
        knight2Tower.p_timePassed = 0.0f;
        knight2Tower.p_upgradesTo = TowerType::KnightLv3;
        knight2Tower.p_id = -1;
        knight2Tower.p_level = 2;
        knight2Tower.p_frameOffset = 0;
        knight2Tower.p_frameAmount = 0;
        knight2Tower.p_typeId = TowerType::KnightLv2;
        knight2Tower.p_tileId = 0;
        knight2Tower.p_isUpgradeHovered = false;
        knight2Tower.p_canUpgrade = true;
        knight2Tower.p_dirty = true;

        g_towerData[TowerType::KnightLv2] = knight2Tower;
#pragma endregion

#pragma region KnightLv3
        // knight Lv 3
        Tower knight3Tower = {};
        knight3Tower.p_fightFunction = [](float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::BigSlash);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = RadiansToDegrees(angle);
            bullet.p_position = enemyPos;
            mgr_bullet->AddBullet(bullet);
        };
        knight3Tower.p_sourceRect = {0, 0, 15, 15};
        knight3Tower.p_price = 200;
        knight3Tower.p_damage = 10;
        knight3Tower.p_position = {-1.0f, -1.0f};
        knight3Tower.p_range = 40.0f;
        knight3Tower.p_attackSpeed = 1.5f;
        knight3Tower.p_timeToAttack = 0.0f;
        knight3Tower.p_timeToNextFrame = 0.0f;
        knight3Tower.p_timePassed = 0.0f;
        knight3Tower.p_upgradesTo = TowerType::KnightLv4;
        knight3Tower.p_id = -1;
        knight3Tower.p_level = 3;
        knight3Tower.p_frameOffset = 0;
        knight3Tower.p_frameAmount = 0;
        knight3Tower.p_typeId = TowerType::KnightLv3;
        knight3Tower.p_tileId = 0;
        knight3Tower.p_isUpgradeHovered = false;
        knight3Tower.p_canUpgrade = true;
        knight3Tower.p_dirty = true;

        g_towerData[TowerType::KnightLv3] = knight3Tower;
#pragma endregion

#pragma region KnightLv4
        // knight Lv 4
        Tower knight4Tower = {};
        knight4Tower.p_fightFunction = [](float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::BigSlash);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = RadiansToDegrees(angle);
            bullet.p_position = enemyPos;
            mgr_bullet->AddBullet(bullet);
        };
        knight4Tower.p_sourceRect = {0, 0, 15, 15};
        knight4Tower.p_price = 550;
        knight4Tower.p_damage = 15;
        knight4Tower.p_position = {-1.0f, -1.0f};
        knight4Tower.p_range = 45.0f;
        knight4Tower.p_attackSpeed = 1.0f;
        knight4Tower.p_timeToAttack = 0.0f;
        knight4Tower.p_timeToNextFrame = 0.0f;
        knight4Tower.p_timePassed = 0.0f;
        knight4Tower.p_upgradesTo = TowerType::KnightLv5;
        knight4Tower.p_id = -1;
        knight4Tower.p_level = 4;
        knight4Tower.p_frameOffset = 0;
        knight4Tower.p_frameAmount = 0;
        knight4Tower.p_typeId = TowerType::KnightLv4;
        knight4Tower.p_tileId = 0;
        knight4Tower.p_isUpgradeHovered = false;
        knight4Tower.p_canUpgrade = true;
        knight4Tower.p_dirty = true;

        g_towerData[TowerType::KnightLv4] = knight4Tower;
#pragma endregion

#pragma region KnightLv5
        // knight Lv 5
        Tower knight5Tower = {};
        knight5Tower.p_fightFunction = [](float deltaTime, Tower *tower, Enemy *enemy, EnemyManager *mgr_enemy, BulletManager *mgr_bullet, TowerManager *mgr_tower)
        {
            Vector2 centerPos = mgr_tower->GetCenterPosition(*tower);
            Vector2 bulletPos = centerPos;
            Vector2 enemyPos = mgr_enemy->GetCenterPosition(*enemy);
            float angle = atan2(enemyPos.y - bulletPos.y, enemyPos.x - bulletPos.x);

            Bullet bullet = Bullets::GetBulletData(BulletType::BiggestSlash);
            bullet.p_id = BulletManager::GetNewValidId();
            bullet.p_damage = tower->p_damage;
            bullet.p_directionAngle = angle;
            bullet.p_rotation = RadiansToDegrees(angle);
            bullet.p_position = enemyPos;
            mgr_bullet->AddBullet(bullet);
        };
        knight5Tower.p_sourceRect = {0, 0, 15, 15};
        knight5Tower.p_price = 1050;
        knight5Tower.p_damage = 40;
        knight5Tower.p_position = {-1.0f, -1.0f};
        knight5Tower.p_range = 50.0f;
        knight5Tower.p_attackSpeed = 1.1f;
        knight5Tower.p_timeToAttack = .0f;
        knight5Tower.p_timeToNextFrame = 0.0f;
        knight5Tower.p_timePassed = 0.0f;
        knight5Tower.p_upgradesTo = TowerType::Nothing;
        knight5Tower.p_id = -1;
        knight5Tower.p_level = 5;
        knight5Tower.p_frameOffset = 0;
        knight5Tower.p_frameAmount = 0;
        knight5Tower.p_typeId = TowerType::KnightLv5;
        knight5Tower.p_tileId = 0;
        knight5Tower.p_isUpgradeHovered = false;
        knight5Tower.p_canUpgrade = false;
        knight5Tower.p_dirty = true;

        g_towerData[TowerType::KnightLv5] = knight5Tower;
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
