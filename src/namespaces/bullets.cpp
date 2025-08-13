#include "bullets.hpp"
#include <cassert>

namespace Bullets
{
    std::unordered_map<int, Bullet> g_bulletData = {};

    void InitBulletData()
    {
        g_bulletData.clear();

#pragma region Shuliken
        // Shuliken bullet
        Bullet shulikenBullet = {};
        
        shulikenBullet.p_updateAnimation = [](const float deltaTime, Bullet& bullet, BulletManager* mgr_bullet) {};
        shulikenBullet.p_sourceRect = {0, 0, 0, 0};
        shulikenBullet.p_position = {-1.0f, -1.0f};
        shulikenBullet.p_id = -1;
        shulikenBullet.p_damage = 0;
        shulikenBullet.p_timeToNextFrame = 0.0f;
        shulikenBullet.p_timePassed = 0.0f;
        shulikenBullet.p_directionAngle = 0.0f;
        shulikenBullet.p_rotation = 0.0f;
        shulikenBullet.p_spinSpeed = 200.0f;
        shulikenBullet.p_speed = 75.0f;
        shulikenBullet.p_typeId = BulletType::Shuliken;
        shulikenBullet.p_pierce = false;
        shulikenBullet.p_alive = true;

        g_bulletData[BulletType::Shuliken] = shulikenBullet;
#pragma endregion

#pragma region SharpShuliken
        // Sharp Shuliken bullet
        Bullet sharpShulikenBullet = {};
        sharpShulikenBullet.p_updateAnimation = [](const float deltaTime, Bullet& bullet, BulletManager* mgr_bullet) {};
        sharpShulikenBullet.p_sourceRect = {0, 0, 0, 0};
        sharpShulikenBullet.p_position = {-1.0f, -1.0f};
        sharpShulikenBullet.p_id = -1;
        sharpShulikenBullet.p_damage = 0;
        sharpShulikenBullet.p_timeToNextFrame = 0.0f;
        sharpShulikenBullet.p_timePassed = 0.0f;
        sharpShulikenBullet.p_directionAngle = 0.0f;
        sharpShulikenBullet.p_rotation = 0.0f;
        sharpShulikenBullet.p_spinSpeed = 225.0f;
        sharpShulikenBullet.p_speed = 85.0f;
        sharpShulikenBullet.p_typeId = BulletType::SharpShuliken;
        sharpShulikenBullet.p_pierce = true;
        sharpShulikenBullet.p_alive = true;

        g_bulletData[BulletType::SharpShuliken] = sharpShulikenBullet;
#pragma endregion

#pragma region Dagger
        // Dagger bullet
        Bullet daggerBullet = {};
        daggerBullet.p_updateAnimation = [](const float deltaTime, Bullet& bullet, BulletManager* mgr_bullet) {};
        daggerBullet.p_sourceRect = {0, 0, 0, 0};
        daggerBullet.p_position = {-1.0f, -1.0f};
        daggerBullet.p_id = -1;
        daggerBullet.p_damage = 0;
        daggerBullet.p_timeToNextFrame = 0.0f;
        daggerBullet.p_timePassed = 0.0f;
        daggerBullet.p_directionAngle = 0.0f;
        daggerBullet.p_rotation = 0.0f;
        daggerBullet.p_spinSpeed = 0.0f;
        daggerBullet.p_speed = 105.0f;
        daggerBullet.p_typeId = BulletType::Dagger;
        daggerBullet.p_pierce = true;
        daggerBullet.p_alive = true;

        g_bulletData[BulletType::Dagger] = daggerBullet;
#pragma endregion

#pragma region Slash
        // Slash bullet 
        Bullet slashBullet = {};
        slashBullet.p_updateAnimation = [](const float deltaTime, Bullet& bullet, BulletManager* mgr_bullet) {};
        slashBullet.p_sourceRect = {0, 0, 8, 8};
        slashBullet.p_position = {-1.0f, -1.0f};
        slashBullet.p_id = -1;
        slashBullet.p_damage = 0;
        slashBullet.p_timeToNextFrame = 0.0f;
        slashBullet.p_timePassed = 0.0f;
        slashBullet.p_directionAngle = 0.0f;
        slashBullet.p_rotation = 0.0f;
        slashBullet.p_spinSpeed = 0.0f;
        slashBullet.p_speed = 0.0f;
        slashBullet.p_typeId = BulletType::Slash;
        slashBullet.p_pierce = true;
        slashBullet.p_alive = true;

        g_bulletData[BulletType::Slash] = slashBullet;
#pragma endregion
    }

    Bullet GetBulletData(int typeId)
    {
        auto it = g_bulletData.find(typeId);
        if (it != g_bulletData.end())
        {
            return it->second;
        }
        assert(false && "couldn't find requested data in bulletData");
        return Bullet{};
    }
}
