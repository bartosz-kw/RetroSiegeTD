#include "enemymanager.hpp"
#include "tilemanager.hpp"
#include "../utility/debugUtil.hpp"
#include "../namespaces/sprites.hpp"
#include <cassert>

constexpr float centerOffset = 7.5f; 

Vector2 EnemyManager::GetCenterPosition(const Enemy& enemy) const
{
    return Vector2{enemy.p_position.x + centerOffset, enemy.p_position.y + centerOffset};
}
uint32_t EnemyManager::FindEnemyInArea(Vector2 center, float radius)
{
    uint16_t biggestWalked = 0;
    uint32_t biggestWalkedId = 0;
    for (auto& enemy : m_enemies)
    {
        Vector2 enemyCenter = {enemy.p_position.x + centerOffset
                              ,enemy.p_position.y + centerOffset};
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
Enemy* EnemyManager::GetEnemyById(uint32_t id)
{
    for (auto& enemy : m_enemies)
    {
        if (enemy.p_id == id)
            return &enemy;
    }
    return nullptr;
}
const uint16_t EnemyManager::GetEnemyTextureIndex(uint16_t typeId) const
{
    return typeId + Sprites::enemyTextureOffset;
}
void EnemyManager::UpdateMovement(Enemy &enemy, float deltaTime)
{
    enemy.p_timeToMove += deltaTime;
    if (enemy.p_timeToMove >= enemy.p_speed)
    {
        Tile positionTile = mgr_tile->GetTile(enemy.p_tileId);
        int16_t moveDirection = positionTile.p_moveDirection;
        if (moveDirection == -5)
        {
            enemy.p_alive = false;
            return;
        }
        enemy.p_tileId = mgr_tile->GetMovedId(enemy.p_tileId, moveDirection);
        enemy.p_timeToMove = false;
        enemy.p_dirty = true;
        enemy.p_walked += 1;
    }
}
void EnemyManager::CleanEnemy(Enemy &enemy)
{
    // check if enemy has valid tile id
    if (enemy.p_tileId == -1)
    {
        enemy.p_tileId = mgr_tile->GetPathStart().p_id;
    }

    // get tile
    Tile tile = mgr_tile->GetTile(enemy.p_tileId);

    // update data
    enemy.p_position = tile.p_position;
    enemy.p_dirty = false;

    assert(tile.p_id != -1);
}
void EnemyManager::RemoveEnemies()
{
    std::vector<size_t> indexesToRemove = {};
    for (size_t i = 0; i < m_enemies.size(); i++)
    {
        if (!m_enemies[i].p_alive)
        {
            indexesToRemove.push_back(i);
        }
    }
    if (indexesToRemove.empty())
        return;
    for (auto it = indexesToRemove.rbegin(); it != indexesToRemove.rend(); ++it)
    {
        m_enemies.erase(m_enemies.begin() + *it);
    }
}
void EnemyManager::Update(float deltaTime)
{
    for (auto &enemy : m_enemies)
    {
        UpdateMovement(enemy, deltaTime);
        RemoveEnemies();
        if (!enemy.p_dirty)
            continue;
        CleanEnemy(enemy);
    }
}
void EnemyManager::Draw(uint8_t screenOffset) const
{
    for (auto &enemy : m_enemies)
    {
        DrawTexture(Sprites::g_textures[GetEnemyTextureIndex(enemy.p_typeId)], enemy.p_position.x + screenOffset, enemy.p_position.y, WHITE);
    }
}
void EnemyManager::InjectDependencies(TileManager *mgr_tilePtr)
{
    mgr_tile = mgr_tilePtr;
}
void EnemyManager::Init()
{
    Enemy enemy = {};
    enemy.p_id = 1;
    enemy.p_tileId = -1;
    enemy.p_typeId = EnemyType::BlueSlime;
    enemy.p_speed = 10;
    m_enemies.push_back(enemy);
}
