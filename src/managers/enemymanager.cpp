#include "enemymanager.hpp"
#include "tilemanager.hpp"
#include "bulletmanager.hpp"
#include "../utility/debugUtil.hpp"
#include "../namespaces/settings.hpp"
#include "../namespaces/basics.hpp"
#include "../managers/psmanager.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/enemies.hpp"
#include <raymath.h>
#include <cassert>

// Private

const uint16_t EnemyManager::GetEnemyTextureIndex(const uint16_t typeId) const
{
    return typeId + Sprites::g_enemyTextureOffset;
}
const Vector2 EnemyManager::CalculateMovePosition(const int16_t moveDirection) const
{
    float dy = 0.0f;
    float dx = 0.0f;
    switch (std::abs(moveDirection))
    {
    case 1:
        dy = -15.0f;
        break;
    case 2:
        dy = +15.0f;
        break;
    case 3:
        dx = +15.0f;
        break;
    case 4:
        dx = -15.0f;
        break;
    default:
        break;
    }
    return Vector2{dx, dy};
}
void EnemyManager::UpdateVisualPosition(Enemy &enemy, const Vector2 &tilePosition, const int16_t moveDirection)
{
    Vector2 movePosition = CalculateMovePosition(moveDirection);

    constexpr float minTime = 0.0f;
    float normalizedTime = (enemy.p_timeToMove - minTime) / (enemy.p_speed - minTime);
    enemy.p_position = Vector2Add(tilePosition, Vector2Scale(movePosition, normalizedTime));
}
void EnemyManager::UpdateMovement(Enemy &enemy, const float deltaTime)
{
    if (enemy.p_tileId == -1)
    {
        return;
    }
    enemy.p_timeToMove += deltaTime;

    Tile positionTile = mgr_tile->GetTile(enemy.p_tileId);
    int16_t moveDirection = positionTile.p_moveDirection;
    if (moveDirection != -5)
    {
        UpdateVisualPosition(enemy, positionTile.p_position, moveDirection);
        if (enemy.p_timeToMove >= enemy.p_speed)
        {
            enemy.p_tileId = mgr_tile->GetMovedId(enemy.p_tileId, moveDirection);
            enemy.p_timeToMove = 0;
            enemy.p_dirty = true;
            enemy.p_walked += 1;
        }
    }
    else
    {
        enemy.p_survived = true;
        return;
    }
}
void EnemyManager::UpdateHitEffect(Enemy &enemy, const float deltaTime)
{
    if (enemy.p_hitEffectTime <= 0)
    {
        return;
    }

    enemy.p_hitEffectTime -= deltaTime;
}
void EnemyManager::UpdateCooldown(Enemy &enemy, const float deltaTime)
{
    std::vector<int> indexsToDelete = {};
    for (size_t i = 0; i < enemy.p_hitCooldowns.size(); i++)
    {
        enemy.p_hitCooldowns[i].first -= deltaTime;
        if (enemy.p_hitCooldowns[i].first <= 0)
        {
            indexsToDelete.push_back(i);
        }
    }
    for (int i = indexsToDelete.size() - 1; i >= 0; i--)
    {
        enemy.p_hitCooldowns.erase(enemy.p_hitCooldowns.begin() + indexsToDelete[i]);
    }
}
void EnemyManager::UpdateAnimation(Enemy &enemy, const float deltaTime)
{
    Basics::Animate(deltaTime, enemy);
}
void EnemyManager::UpdateEnemy(Enemy &enemy, const float deltaTime)
{
    if (enemy.p_dirty)
    {
        CleanEnemy(enemy);
    }
    

    HandleHits(enemy);
    UpdateMovement(enemy, deltaTime);
    UpdateCooldown(enemy, deltaTime);
    UpdateHitEffect(enemy, deltaTime);
    UpdateAnimation(enemy, deltaTime);
    if (enemy.p_updateFunction)
    {
        enemy.p_updateFunction(deltaTime, enemy, this);
    }
    else
    {
        PrintDebugError(enemy.p_id, "Invalid Function Enemy ID");
        PrintDebugError(enemy.p_typeId, "Invalid Function Enemy TypeID");
    }
}
void EnemyManager::HandleHits(Enemy &enemy)
{
    constexpr float hitCooldown = 3.0f;
    constexpr float hitEffectTime = 0.4f;
    const Rectangle enemyRect = {enemy.p_position.x, enemy.p_position.y, (float)enemy.p_sourceRect.width, (float)enemy.p_sourceRect.height};

    std::vector<Bullet *> detectedBullets = mgr_bullet->GetBulletsFromArea(enemyRect);
    for (auto bullet : detectedBullets)
    {
        bool bulletOnCooldown = false;
        for (size_t i = 0; i < enemy.p_hitCooldowns.size(); i++)
        {
            if (enemy.p_hitCooldowns[i].second == bullet->p_id)
            {
                bulletOnCooldown = true;
                continue;
            };
        }
        if (bulletOnCooldown)
        {
            continue;
        }

        if (!bullet->p_alive)
        {
            continue;
        }
        else if (!bullet->p_pierce)
        {
            bullet->p_alive = false;
        }
        else
        {
            enemy.p_hitCooldowns.push_back({hitCooldown, bullet->p_id});
        }

        enemy.p_health -= bullet->p_damage;
        enemy.p_hitEffectTime = hitEffectTime;
    }
}
void EnemyManager::CheckForHover()
{
    const Vector2 mousePosition = GetMousePosition();
    for (auto &enemy : m_enemies)
    {
        Rectangle rect =
            {
                (Settings::g_boundingSize + enemy.p_position.x) * Settings::g_gameScale,
                enemy.p_position.y * Settings::g_gameScale,
                enemy.p_sourceRect.width * Settings::g_gameScale,
                enemy.p_sourceRect.height * Settings::g_gameScale};
        if (CheckCollisionPointRec(mousePosition, rect))
        {
            m_hoveredEnemy = &enemy;
            return;
        }
    }
    m_hoveredEnemy = nullptr;
}
void EnemyManager::PreKillEnemy(Enemy &enemy)
{
    if (!enemy.p_alive)
    {
        mgr_ps->AddMoney(enemy.p_moneyDrop);
    }
    else if (enemy.p_survived)
    {
        mgr_ps->SubHealth(enemy.p_health);
    }
}
void EnemyManager::CleanEnemy(Enemy &enemy)
{
    if (enemy.p_tileId == -1)
    {
        enemy.p_tileId = mgr_tile->GetPathStart().p_id;
    }

    const Tile tile = mgr_tile->GetTile(enemy.p_tileId);
    if (tile.p_id == -1)
    {
        return;
    }

    enemy.p_position = tile.p_position;
    enemy.p_dirty = false;
}

// Public

void EnemyManager::RemoveEnemies()
{
    std::vector<size_t> indexesToRemove = {};
    for (size_t i = 0; i < m_enemies.size(); i++)
    {
        if (!m_enemies[i].p_alive || m_enemies[i].p_survived)
        {
            indexesToRemove.push_back(i);
        }
    }
    if (indexesToRemove.empty())
        return;
    for (auto it = indexesToRemove.rbegin(); it != indexesToRemove.rend(); ++it)
    {
        PreKillEnemy(m_enemies.at(*it));
        m_enemies.erase(m_enemies.begin() + *it);
    }
}
bool EnemyManager::IsEnemiesEmpty() const
{
    return m_enemies.empty();
}
uint32_t EnemyManager::GetNewValidId()
{
    return m_IdCounter++;
}
Vector2 EnemyManager::GetCenterPosition(const Enemy &enemy) const
{
    return Vector2{enemy.p_position.x + enemy.p_sourceRect.width / 2.0f, enemy.p_position.y + enemy.p_sourceRect.height / 2.0f};
}
uint32_t EnemyManager::FindEnemyInArea(const Vector2 center, const float radius)
{
    int32_t biggestWalked = -10000;
    uint32_t biggestWalkedId = 0;
    for (auto &enemy : m_enemies)
    {
        Vector2 enemyCenter = GetCenterPosition(enemy);
        if (CheckCollisionPointCircle(enemyCenter, center, radius))
        {
            if (biggestWalked < enemy.p_walked)
            {
                biggestWalked = enemy.p_walked;
                biggestWalkedId = enemy.p_id;
            }
        }
    }
    return biggestWalkedId;
}
Enemy *EnemyManager::GetEnemyById(const uint32_t id)
{
    for (auto &enemy : m_enemies)
    {
        if (enemy.p_id == id)
            return &enemy;
    }
    return nullptr;
}
const Enemy *EnemyManager::GetHoveredEnemy() const
{
    return m_hoveredEnemy;
}
void EnemyManager::AddEnemy(const Enemy enemy)
{
    m_enemies.push_back(enemy);
}
void EnemyManager::SpawnEnemy(const EnemyType enemyType)
{
    Enemy enemy = Enemies::GetEnemyData(enemyType);
    enemy.p_tileId = -1;
    enemy.p_id = GetNewValidId();
    AddEnemy(enemy);
}
void EnemyManager::ReserveEnemies(const uint16_t amount)
{
    m_enemies.reserve(amount);
}
void EnemyManager::ClearEnemiesVector()
{
    m_enemies.clear();
}
void EnemyManager::Update(const float deltaTime)
{
    for (auto &enemy : m_enemies)
    {
        if (enemy.p_health <= 0)
        {
            enemy.p_alive = false;
            continue;
        }

        UpdateEnemy(enemy, deltaTime);
    }
    CheckForHover();
    RemoveEnemies();
}
void EnemyManager::Draw(const uint8_t screenOffset) const
{
    for (auto &enemy : m_enemies)
    {
        if (enemy.p_dirty)
        {
           // continue;
        }

        Color color = WHITE;
        if (enemy.p_hitEffectTime > 0.0f)
        {
            color = {230, 41, 55, 255};
        }

        constexpr Vector2 origin = {0.0f, 0.0f};
        const Texture2D texture = Sprites::g_textures[GetEnemyTextureIndex(enemy.p_typeId)];
        const Vector2 position = {floorf(enemy.p_position.x + screenOffset), floorf(enemy.p_position.y)};
        const Rectangle dest = {position.x, position.y, static_cast<float>(enemy.p_sourceRect.width), static_cast<float>(enemy.p_sourceRect.height)};
        DrawTexturePro(texture, enemy.p_sourceRect, dest, origin, 0.0f, color);

        // DrawPixel(GetCenterPosition(enemy).x + Settings::g_boundingSize, GetCenterPosition(enemy).y, RED);
    }
}
void EnemyManager::InjectDependencies(TileManager *mgr_tilePtr, BulletManager *mgr_bulletPtr, PSManager *mgr_psPtr)
{
    mgr_tile = mgr_tilePtr;
    mgr_bullet = mgr_bulletPtr;
    mgr_ps = mgr_psPtr;
}
void EnemyManager::Init()
{
}
