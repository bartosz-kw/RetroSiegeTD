#include "enemies.hpp"
#include "basics.hpp"
#include "../managers/enemymanager.hpp"
#include "../utility/debugUtil.hpp"
#include <cassert>

namespace Enemies
{
        std::unordered_map<int, Enemy> g_enemyData = {};

        void InitEnemyData()
        {
                g_enemyData.clear();

#pragma region BlueSlime
                Enemy blueSlime = {};
                blueSlime.p_hitCooldowns = {};
                blueSlime.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager* mgr_enemy) {};
                blueSlime.p_sourceRect = {0, 0, 15, 15};
                blueSlime.p_moneyDrop = 10;
                blueSlime.p_health = 10;
                blueSlime.p_position = {-1.0f, -1.0f};
                blueSlime.p_id = 0;
                blueSlime.p_speed = 1.5f;
                blueSlime.p_timeToNextFrame = 1.0f;
                blueSlime.p_timePassed = 0.0f;
                blueSlime.p_timeToMove = 0.0f;
                blueSlime.p_hitEffectTime = 0.0f;
                blueSlime.p_typeId = EnemyType::BlueSlime;
                blueSlime.p_walked = 0;
                blueSlime.p_tileId = -1;
                blueSlime.p_frameOffset = 15;
                blueSlime.p_frameAmount = 2;
                blueSlime.p_alive = true;
                blueSlime.p_survived = false;
                blueSlime.p_dirty = true;

                g_enemyData[EnemyType::BlueSlime] = blueSlime;
#pragma endregion

#pragma region RedSlime
                Enemy redSlime = {};
                redSlime.p_hitCooldowns = {};
                redSlime.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager* mgr_enemy) {};
                redSlime.p_sourceRect = {0, 0, 15, 15};
                redSlime.p_moneyDrop = 15;
                redSlime.p_health = 50;
                redSlime.p_position = {-1.0f, -1.0f};
                redSlime.p_id = 0;
                redSlime.p_speed = 2.0f;
                redSlime.p_timeToNextFrame = 1.0f;
                redSlime.p_timePassed = 0.0f;
                redSlime.p_timeToMove = 0.0f;
                redSlime.p_hitEffectTime = 0.0f;
                redSlime.p_typeId = EnemyType::RedSlime;
                redSlime.p_walked = 0;
                redSlime.p_tileId = -1;
                redSlime.p_frameOffset = 15;
                redSlime.p_frameAmount = 2;
                redSlime.p_alive = true;
                redSlime.p_survived = false;
                redSlime.p_dirty = true;

                g_enemyData[EnemyType::RedSlime] = redSlime;
#pragma endregion

#pragma region Zombie
                Enemy zombie = {};
                zombie.p_hitCooldowns = {};
                zombie.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager* mgr_enemy) {};
                zombie.p_sourceRect = {0, 0, 15, 15};
                zombie.p_moneyDrop = 25;
                zombie.p_health = 75;
                zombie.p_position = {-1.0f, -1.0f};
                zombie.p_id = 0;
                zombie.p_speed = 1.0f;
                zombie.p_timeToNextFrame = 0.5f;
                zombie.p_timePassed = 0.0f;
                zombie.p_timeToMove = 0.0f;
                zombie.p_hitEffectTime = 0.0f;
                zombie.p_typeId = EnemyType::Zombie;
                zombie.p_walked = 0;
                zombie.p_tileId = -1;
                zombie.p_frameOffset = 15;
                zombie.p_frameAmount = 2;
                zombie.p_alive = true;
                zombie.p_survived = false;
                zombie.p_dirty = true;

                g_enemyData[EnemyType::Zombie] = zombie;
#pragma endregion

#pragma region ArmoredZombie
                Enemy armoredZombie = {};
                armoredZombie.p_hitCooldowns = {};
                armoredZombie.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager* mgr_enemy) {};
                armoredZombie.p_sourceRect = {0, 0, 15, 15};
                armoredZombie.p_moneyDrop = 35;
                armoredZombie.p_health = 150;
                armoredZombie.p_position = {-1.0f, -1.0f};
                armoredZombie.p_id = 0;
                armoredZombie.p_speed = 1.0f;
                armoredZombie.p_timeToNextFrame = 0.5f;
                armoredZombie.p_timePassed = 0.0f;
                armoredZombie.p_timeToMove = 0.0f;
                armoredZombie.p_hitEffectTime = 0.0f;
                armoredZombie.p_typeId = EnemyType::ArmoredZombie;
                armoredZombie.p_walked = 0;
                armoredZombie.p_tileId = -1;
                armoredZombie.p_frameOffset = 15;
                armoredZombie.p_frameAmount = 2;
                armoredZombie.p_alive = true;
                armoredZombie.p_survived = false;
                armoredZombie.p_dirty = true;

                g_enemyData[EnemyType::ArmoredZombie] = armoredZombie;
#pragma endregion

#pragma region Skeleton
                Enemy skeleton = {};
                skeleton.p_hitCooldowns = {};
                skeleton.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager* mgr_enemy) {};
                skeleton.p_sourceRect = {0, 0, 15, 15};
                skeleton.p_moneyDrop = 25;
                skeleton.p_health = 50;
                skeleton.p_position = {-1.0f, -1.0f};
                skeleton.p_id = 0;
                skeleton.p_speed = 0.5f;
                skeleton.p_timeToNextFrame = 0.25f;
                skeleton.p_timePassed = 0.0f;
                skeleton.p_timeToMove = 0.0f;
                skeleton.p_hitEffectTime = 0.0f;
                skeleton.p_typeId = EnemyType::Skeleton;
                skeleton.p_walked = 0;
                skeleton.p_tileId = -1;
                skeleton.p_frameOffset = 15;
                skeleton.p_frameAmount = 2;
                skeleton.p_alive = true;
                skeleton.p_survived = false;
                skeleton.p_dirty = true;

                g_enemyData[EnemyType::Skeleton] = skeleton;
#pragma endregion

#pragma region Summoner
                Enemy summoner = {};
                summoner.p_hitCooldowns = {};
                summoner.p_updateFunction = [](const float deltaTime, Enemy &enemy, EnemyManager* mgr_enemy)
                {
                    constexpr float spawnCooldown = 2.5f;
                    static float time = 0.0f;
                    time += deltaTime;
                    if (time >= spawnCooldown)
                    {
                       time = 0.0f;
                       Enemy summon = GetEnemyData(EnemyType::Skeleton);
                       summon.p_moneyDrop = 0.0f;
                       summon.p_id = mgr_enemy->GetNewValidId();
                       summon.p_tileId = enemy.p_tileId;
                       summon.p_walked = enemy.p_walked;
                       mgr_enemy->AddEnemy(summon);
                    }
                };
                summoner.p_sourceRect = {0, 0, 15, 15};
                summoner.p_moneyDrop = 100;
                summoner.p_health = 300;
                summoner.p_position = {-1.0f, -1.0f};
                summoner.p_id = 0;
                summoner.p_speed = 2.0f;
                summoner.p_timeToNextFrame = 0.25f;
                summoner.p_timePassed = 0.0f;
                summoner.p_timeToMove = 0.0f;
                summoner.p_hitEffectTime = 0.0f;
                summoner.p_typeId = EnemyType::Summoner;
                summoner.p_walked = 0;
                summoner.p_tileId = -1;
                summoner.p_frameOffset = 15;
                summoner.p_frameAmount = 2;
                summoner.p_alive = true;
                summoner.p_survived = false;
                summoner.p_dirty = true;

                g_enemyData[EnemyType::Summoner] = summoner;
#pragma endregion
        }

        Enemy GetEnemyData(const int typeId)
        {
                auto it = g_enemyData.find(typeId);
                if (it != g_enemyData.end())
                {
                        return it->second;
                }
                assert(false && "couldn't find requested data in enemyData");
                return Enemy{};
        }
}
