#include "bullets.hpp"
#include <cassert>

namespace Bullets
{
    std::unordered_map<int, Bullet> g_bulletData = {};

    void InitBulletData()
    {
        g_bulletData.clear();

        // Shuliken bullet
        Bullet shulikenBullet = {};
        shulikenBullet.p_position = {-1.0f, -1.0f};
        shulikenBullet.p_id = -1;
        shulikenBullet.p_damage = 0;
        shulikenBullet.p_directionAngle = 0.0f;
        shulikenBullet.p_rotation = 0.0f;
        shulikenBullet.p_spinSpeed = 200.0f;
        shulikenBullet.p_speed = 75.0f;
        shulikenBullet.p_typeId = BulletType::Shuliken;
        shulikenBullet.p_pierce = true;
        shulikenBullet.p_spinning = true;
        shulikenBullet.p_alive = true;

        g_bulletData[BulletType::Shuliken] = shulikenBullet;
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
