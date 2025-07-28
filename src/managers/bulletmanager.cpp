#include "bulletmanager.hpp"
#include "../namespaces/sprites.hpp"
#include <raylib.h>
#include <algorithm>

uint16_t BulletManager::GetBulletTextureIndex(uint16_t typeId) const
{
    return typeId + Sprites::buttetTextureOffset;
}

void BulletManager::AddBullet(const Bullet& bullet)
{
    m_bullets.push_back(bullet);
}

void BulletManager::RemoveBullet(int32_t id)
{
    m_bullets.erase
    (
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [id](const Bullet& b) { return b.p_id == id; }),
        m_bullets.end()
    );
}

void BulletManager::Update(float deltaTime)
{
    for (auto& bullet : m_bullets)
    {

    }
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