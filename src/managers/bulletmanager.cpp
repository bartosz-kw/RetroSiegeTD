#include "bulletmanager.hpp"
#include "../namespaces/sprites.hpp"
#include "../utility/debugUtil.hpp"
#include <raylib.h>
#include <cmath>
#include <algorithm>

uint16_t BulletManager::GetBulletTextureIndex(uint16_t typeId) const
{
    return typeId + Sprites::buttetTextureOffset;
}

void BulletManager::AddBullet(Bullet bullet)
{
    m_bullets.push_back(bullet);
}
void BulletManager::RemoveBullets()
{
    std::vector<size_t> indexesToRemove = {};
    for (size_t i = 0; i < m_bullets.size(); i++)
    {
        if (!m_bullets[i].p_alive)
        {
            indexesToRemove.push_back(i);
        }
    }
    if (indexesToRemove.empty())
        return;
    for (auto it = indexesToRemove.rbegin(); it != indexesToRemove.rend(); ++it)
    {
        m_bullets.erase(m_bullets.begin() + *it);
        PrintDebug("Bullet removed");
    }
}
void BulletManager::Update(float deltaTime)
{
    for (auto& bullet : m_bullets)
    {
        bullet.p_position.x += cos(bullet.p_angle) * bullet.p_speed;
        bullet.p_position.y += sin(bullet.p_angle) * bullet.p_speed;
        // TODO: Split this into smaller chunks and include sprite bounds in this detection logic
        if (bullet.p_position.x <= 0
          ||bullet.p_position.x >= 270
          ||bullet.p_position.y <= 0
          ||bullet.p_position.y >= 270)
        {
            bullet.p_alive = false;
        }
        
    }
    RemoveBullets();
}

void BulletManager::Draw(uint8_t screenOffset) const
{
    for (const auto& bullet : m_bullets)
    {
        DrawTexture(
            Sprites::g_textures[GetBulletTextureIndex(bullet.p_typeId)], // Replace 0 with bullet type if needed
            static_cast<int>(bullet.p_position.x + screenOffset),
            static_cast<int>(bullet.p_position.y),
            WHITE
        );
    }
}
void BulletManager::Init()
{
    m_bullets.clear();
}