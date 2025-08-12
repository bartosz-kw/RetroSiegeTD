#include "enemymanager.hpp"
#include "tilemanager.hpp"
#include "bulletmanager.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/psmanager.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/enemies.hpp"
#include <raymath.h>
#include <cassert>

// Private

const uint16_t EnemyManager::GetEnemyTextureIndex(const uint16_t typeId) const
{
    return typeId + Sprites::enemyTextureOffset;
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
void EnemyManager::HandleHits(Enemy &enemy)
{
    const Texture2D texture = Sprites::g_textures[GetEnemyTextureIndex(enemy.p_typeId)];
    const Rectangle enemyRect = {enemy.p_position.x, enemy.p_position.y, (float)texture.width, (float)texture.height};

    std::vector<Bullet*> detectedBullets = mgr_bullet->GetBulletsFromArea(enemyRect);
    for (auto bullet : detectedBullets)
    {
        enemy.p_health -= bullet->p_damage;
        // PrintDebug(enemy.p_health, "HIT TAKEN");
    }
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
    // check if enemy has valid tile id
    if (enemy.p_tileId == -1)
    {
        enemy.p_tileId = mgr_tile->GetPathStart().p_id;
        ;
    }

    // get tile
    const Tile tile = mgr_tile->GetTile(enemy.p_tileId);

    // update data
    enemy.p_position = tile.p_position;
    enemy.p_dirty = false;

    assert(tile.p_id != -1);
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
    Texture2D enemyTexture = Sprites::g_textures[GetEnemyTextureIndex(enemy.p_typeId)];
    return Vector2{enemy.p_position.x + enemyTexture.width / 2.0f, enemy.p_position.y + enemyTexture.height / 2.0f};
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
void EnemyManager::AddEnemy(Enemy enemy)
{
    m_enemies.push_back(enemy);
}
void EnemyManager::ClearEnemies()
{
    m_enemies.clear();
}
void EnemyManager::Update(float deltaTime)
{
    for (auto &enemy : m_enemies)
    {
        if (enemy.p_health <= 0)
        {
            enemy.p_alive = false;
        }

        UpdateMovement(enemy, deltaTime);
        HandleHits(enemy);
        if (enemy.p_dirty)
        {
            CleanEnemy(enemy);
        }
    }
    RemoveEnemies();
}
void EnemyManager::Draw(uint8_t screenOffset) const
{
    for (auto &enemy : m_enemies)
    {
        if (enemy.p_dirty)
        {
            continue;
        }

        DrawTexture(Sprites::g_textures[GetEnemyTextureIndex(enemy.p_typeId)], enemy.p_position.x + screenOffset, enemy.p_position.y, WHITE);
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
