#include "bulletmanager.hpp"
#include "../namespaces/sprites.hpp"
#include "../utility/debugUtil.hpp"
#include <raylib.h>
#include <cmath>
#include <algorithm>

// Private

int32_t BulletManager::g_nextBulletId = -1;

uint16_t BulletManager::GetBulletTextureIndex(const uint16_t typeId) const
{
    return typeId + Sprites::g_buttetTextureOffset;
}
void BulletManager::UpdatePosition(Bullet &bullet, const float deltaTime)
{
    bullet.p_position.x += cos(bullet.p_directionAngle) * bullet.p_speed * deltaTime;
    bullet.p_position.y += sin(bullet.p_directionAngle) * bullet.p_speed * deltaTime;

    if (bullet.p_spinSpeed != 0)
    {
        bullet.p_rotation += bullet.p_spinSpeed * deltaTime;
    }
}
void BulletManager::UpdateAnimations(Bullet &bullet, const float deltaTime)
{
    bullet.p_updateAnimation(deltaTime,bullet);
}
void BulletManager::ValidatePosition(Bullet &bullet)
{
    const Texture2D bulletTexture = Sprites::g_textures[GetBulletTextureIndex(bullet.p_typeId)];
    const int width = bulletTexture.width;
    const int height = bulletTexture.height;

    if (bullet.p_position.x <= 0 - width || bullet.p_position.x >= 270 + width || bullet.p_position.y <= 0 - height || bullet.p_position.y >= 270 + height)
    {
        bullet.p_alive = false;
    }
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
    {
        return;
    }
    for (auto it = indexesToRemove.rbegin(); it != indexesToRemove.rend(); ++it)
    {
        m_bullets.erase(m_bullets.begin() + *it);
    }
}
// Public

std::vector<Bullet *> BulletManager::GetBulletsFromArea(const Rectangle area)
{
    std::vector<Bullet *> detectedBullets = {};
    for (auto &bullet : m_bullets)
    {
        const Texture2D bulletTexture = Sprites::g_textures[GetBulletTextureIndex(bullet.p_typeId)];
        const Vector2 pos = bullet.p_position;
        const Rectangle bulletRect = {pos.x, pos.y, static_cast<float>(bulletTexture.width), static_cast<float>(bulletTexture.height)};
        if (CheckCollisionRecs(area, bulletRect))
        {
            detectedBullets.push_back(&bullet);
        }
    }
    return detectedBullets;
}
int32_t BulletManager::GetNewValidId()
{
    return g_nextBulletId++;
}
void BulletManager::AddBullet(const Bullet bullet)
{
    m_bullets.push_back(bullet);
}
void BulletManager::Update(const float deltaTime)
{
    for (auto &bullet : m_bullets)
    {
        UpdatePosition(bullet, deltaTime);
        UpdateAnimations(bullet,deltaTime);
        ValidatePosition(bullet);
    }
    RemoveBullets();
}
void BulletManager::Draw(const uint8_t screenOffset) const
{
    for (const auto &bullet : m_bullets)
    {
        const Texture2D texture = Sprites::g_textures[GetBulletTextureIndex(bullet.p_typeId)];
        const Vector2 position = {bullet.p_position.x + screenOffset, bullet.p_position.y};

        if (bullet.p_sourceRect.width == 0 && bullet.p_sourceRect.height == 0)
        {
            const Vector2 origin = {static_cast<float>(texture.width) / 2.0f, static_cast<float>(texture.height) / 2.0f};
            const Rectangle dest = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
            const Rectangle source = {0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};
            DrawTexturePro(texture, source, dest, origin, bullet.p_rotation, WHITE);
        }
        else
        {
            const Rectangle dest = {position.x, position.y, static_cast<float>(bullet.p_sourceRect.width), static_cast<float>(bullet.p_sourceRect.width)};
            const Vector2 origin = {static_cast<float>(bullet.p_sourceRect.width) / 2.0f, static_cast<float>(bullet.p_sourceRect.height) / 2.0f};
            DrawTexturePro(texture, bullet.p_sourceRect, dest, origin, bullet.p_rotation, WHITE);
        }
    }
}
Vector2 BulletManager::GetCenterPosition(const Bullet &bullet) const
{
    const Texture2D bulletTexture = Sprites::g_textures[GetBulletTextureIndex(bullet.p_typeId)];
    return Vector2{bullet.p_position.x + bulletTexture.width / 2.0f, bullet.p_position.y + bulletTexture.height / 2.0f};
}

void BulletManager::Init()
{
    g_nextBulletId = 1;
    m_bullets.clear();
}
