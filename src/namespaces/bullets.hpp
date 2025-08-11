#pragma once

#include <unordered_map>
#include <cassert>
#include "../structs/bullet.hpp"

namespace Bullets
{
    inline std::unordered_map<int, Bullet> g_bulletData =
    {
        // position, id, damage, directionAngle, rotation, spinSpeed, speed, typeId, spinning, alive
        {BulletType::Shuliken, Bullet{{-1, -1}, -1, 0, 0.0f, 0.0f, 200.0f, 75.0f, BulletType::Shuliken, true, true}}
    };

    inline Bullet GetBulletData(const int typeId)
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
