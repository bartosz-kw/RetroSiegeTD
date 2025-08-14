#include "enemies.hpp"
#include <cassert>

namespace Enemies
{
    std::unordered_map<int, Enemy> g_enemyData = {};

    void InitEnemyData()
    {
        g_enemyData.clear();

#pragma region BlueSlime

        // Blue Slime
        Enemy blueSlime = {};
        blueSlime.p_hitCooldowns = {};
        blueSlime.p_updateAnimation = [](const float deltaTime, Enemy &enemy)
        {
            constexpr uint8_t frameOffset = 15;
            constexpr uint8_t frameAmount = 2;

            enemy.p_timePassed += deltaTime;
            if (enemy.p_timePassed >= enemy.p_timeToNextFrame)
            {
                enemy.p_timePassed = 0.0f;
                if (enemy.p_sourceRect.x + frameOffset > frameOffset * (frameAmount - 1))
                {
                    enemy.p_sourceRect = {0,0,frameOffset,enemy.p_sourceRect.height};
                }
                else
                {
                    enemy.p_sourceRect.x += frameOffset;
                }
            }
        };
        blueSlime.p_sourceRect = {0, 0, 15, 15};
        blueSlime.p_moneyDrop = 10;
        blueSlime.p_health = 10;
        blueSlime.p_position = {-1.0f, -1.0f};
        blueSlime.p_id = 1;
        blueSlime.p_speed = 1.5f;
        blueSlime.p_timeToNextFrame = 1.0f;
        blueSlime.p_timePassed = 0.0f;
        blueSlime.p_timeToMove = 0.0f;
        blueSlime.p_hitEffectTime = 0.0f;
        blueSlime.p_typeId = EnemyType::BlueSlime;
        blueSlime.p_walked = 0;
        blueSlime.p_tileId = -1;
        blueSlime.p_alive = true;
        blueSlime.p_survived = false;
        blueSlime.p_dirty = true;

        g_enemyData[EnemyType::BlueSlime] = blueSlime;
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
