#include "bullets.hpp"
#include "basics.hpp"
#include <cassert>

namespace Bullets
{
    std::unordered_map<int, Bullet> g_bulletData = {};

    void InitBulletData()
    {
        g_bulletData.clear();

#pragma region Shuliken
        Bullet shulikenBullet = {};

        shulikenBullet.p_sourceRect = {0, 0, 9, 9};
        shulikenBullet.p_hitboxBonus = {0,0};
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
        shulikenBullet.p_frameAmount = 0;
        shulikenBullet.p_frameOffset = 0;
        shulikenBullet.p_pierce = false;
        shulikenBullet.p_removeAfterAnimation = false;
        shulikenBullet.p_alive = true;

        g_bulletData[BulletType::Shuliken] = shulikenBullet;
#pragma endregion

#pragma region SharpShuliken
        Bullet sharpShulikenBullet = {};
        sharpShulikenBullet.p_sourceRect = {0, 0, 9, 9};
        sharpShulikenBullet.p_hitboxBonus = {0,0};
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
        sharpShulikenBullet.p_frameAmount = 0;
        sharpShulikenBullet.p_frameOffset = 0;
        sharpShulikenBullet.p_pierce = true;
        sharpShulikenBullet.p_removeAfterAnimation = false;
        sharpShulikenBullet.p_alive = true;

        g_bulletData[BulletType::SharpShuliken] = sharpShulikenBullet;
#pragma endregion

#pragma region Dagger
        Bullet daggerBullet = {};
        daggerBullet.p_sourceRect = {0, 0, 7, 3};
        daggerBullet.p_hitboxBonus = {0,0};
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
        daggerBullet.p_frameAmount = 0;
        daggerBullet.p_frameOffset = 0;
        daggerBullet.p_pierce = true;
        daggerBullet.p_removeAfterAnimation = false;
        daggerBullet.p_alive = true;

        g_bulletData[BulletType::Dagger] = daggerBullet;
#pragma endregion

#pragma region Slash
        Bullet slashBullet = {};
        slashBullet.p_sourceRect = {0, 0, 8, 8};
        slashBullet.p_hitboxBonus = {10.0f,10.0f};
        slashBullet.p_position = {-1.0f, -1.0f};
        slashBullet.p_id = -1;
        slashBullet.p_damage = 0;
        slashBullet.p_timeToNextFrame = 0.05f;
        slashBullet.p_timePassed = 0.0f;
        slashBullet.p_directionAngle = 0.0f;
        slashBullet.p_rotation = 0.0f;
        slashBullet.p_spinSpeed = 0.0f;
        slashBullet.p_speed = 0.0f;
        slashBullet.p_typeId = BulletType::Slash;
        slashBullet.p_frameAmount = 8;
        slashBullet.p_frameOffset = 8;
        slashBullet.p_pierce = true;
        slashBullet.p_removeAfterAnimation = true;
        slashBullet.p_alive = true;

        g_bulletData[BulletType::Slash] = slashBullet;
#pragma endregion

#pragma region SpearSlash
        Bullet spearSlashBullet = {};


        spearSlashBullet.p_sourceRect = {0, 0, 8, 8};
        spearSlashBullet.p_hitboxBonus = {0,0};
        spearSlashBullet.p_position = {-1.0f, -1.0f};
        spearSlashBullet.p_id = -1;
        spearSlashBullet.p_damage = 0;
        spearSlashBullet.p_timeToNextFrame = 0.05f;
        spearSlashBullet.p_timePassed = 0.0f;
        spearSlashBullet.p_directionAngle = 0.0f;
        spearSlashBullet.p_rotation = 0.0f;
        spearSlashBullet.p_spinSpeed = 0.0f;
        spearSlashBullet.p_speed = 0.0f;
        spearSlashBullet.p_typeId = BulletType::SpearSlash;
        spearSlashBullet.p_frameAmount = 6;
        spearSlashBullet.p_frameOffset = 8;
        spearSlashBullet.p_pierce = true;
        spearSlashBullet.p_removeAfterAnimation = true;
        spearSlashBullet.p_alive = true;

        g_bulletData[BulletType::SpearSlash] = spearSlashBullet;
#pragma endregion

#pragma region BigSlash
        Bullet bigSlashBullet = {};

        bigSlashBullet.p_sourceRect = {0, 0, 8, 8};
        bigSlashBullet.p_hitboxBonus = {17.5f,15.0f};
        bigSlashBullet.p_position = {-1.0f, -1.0f};
        bigSlashBullet.p_id = -1;
        bigSlashBullet.p_damage = 0;
        bigSlashBullet.p_timeToNextFrame = 0.05f;
        bigSlashBullet.p_timePassed = 0.0f;
        bigSlashBullet.p_directionAngle = 0.0f;
        bigSlashBullet.p_rotation = 0.0f;
        bigSlashBullet.p_spinSpeed = 0.0f;
        bigSlashBullet.p_speed = 0.0f;
        bigSlashBullet.p_typeId = BulletType::BigSlash;
        bigSlashBullet.p_frameAmount = 8;
        bigSlashBullet.p_frameOffset = 8;
        bigSlashBullet.p_pierce = true;
        bigSlashBullet.p_removeAfterAnimation = true;
        bigSlashBullet.p_alive = true;

        g_bulletData[BulletType::BigSlash] = bigSlashBullet;
#pragma endregion

#pragma region BiggestSlash
        Bullet biggestSlashBullet = {};

        biggestSlashBullet.p_sourceRect = {0, 0, 10, 10};
        biggestSlashBullet.p_hitboxBonus = {25.0f,20.0f};
        biggestSlashBullet.p_position = {-1.0f, -1.0f};
        biggestSlashBullet.p_id = -1;
        biggestSlashBullet.p_damage = 0;
        biggestSlashBullet.p_timeToNextFrame = 0.05f;
        biggestSlashBullet.p_timePassed = 0.0f;
        biggestSlashBullet.p_directionAngle = 0.0f;
        biggestSlashBullet.p_rotation = 0.0f;
        biggestSlashBullet.p_spinSpeed = 0.0f;
        biggestSlashBullet.p_speed = 0.0f;
        biggestSlashBullet.p_typeId = BulletType::BiggestSlash;
        biggestSlashBullet.p_frameAmount = 8;
        biggestSlashBullet.p_frameOffset = 10;
        biggestSlashBullet.p_pierce = true;
        biggestSlashBullet.p_removeAfterAnimation = true;
        biggestSlashBullet.p_alive = true;

        g_bulletData[BulletType::BiggestSlash] = biggestSlashBullet;
#pragma endregion

#pragma region SniperBullet
        Bullet sniperBullet = {};

        sniperBullet.p_sourceRect = {0, 0, 10, 1};
        sniperBullet.p_hitboxBonus = {0,0};
        sniperBullet.p_position = {-1.0f, -1.0f};
        sniperBullet.p_id = -1;
        sniperBullet.p_damage = 0;
        sniperBullet.p_timeToNextFrame = 0.0f;
        sniperBullet.p_timePassed = 0.0f;
        sniperBullet.p_directionAngle = 0.0f;
        sniperBullet.p_rotation = 0.0f;
        sniperBullet.p_spinSpeed = 0.0f;
        sniperBullet.p_speed = 500.0f;
        sniperBullet.p_typeId = BulletType::SniperBullet;
        sniperBullet.p_frameAmount = 0;
        sniperBullet.p_frameOffset = 0;
        sniperBullet.p_pierce = false;
        sniperBullet.p_removeAfterAnimation = false;
        sniperBullet.p_alive = true;

        g_bulletData[BulletType::SniperBullet] = sniperBullet;
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
