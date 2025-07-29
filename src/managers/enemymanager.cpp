#include "enemymanager.hpp"
#include "tilemanager.hpp"
#include "../utility/debugUtil.hpp"
#include "../namespaces/sprites.hpp"
#include <cassert>

int16_t EnemyManager::FindEnemyInArea(Vector2 center, float radius)
{
    for (auto& enemy : m_enemies)
    {
        Vector2 enemyCenter = {enemy.p_position.x/2,enemy.p_position.y/2};
        if (CheckCollisionPointCircle(enemyCenter, center, radius))
        {
            return enemy.p_id;
        }
    }
    return -1;
}
Enemy* EnemyManager::GetEnemyById(int16_t id)
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
        int16_t moveDirection = mgr_tile->GetTile(enemy.p_tileId).p_moveDirection;
        if (moveDirection == -5)
        {
            enemy.p_alive = false;
            return;
        }
        enemy.p_tileId = mgr_tile->GetMovedId(enemy.p_tileId, moveDirection);
        enemy.p_timeToMove = false;
        enemy.p_dirty = true;
    }
}
void EnemyManager::CleanEnemy(Enemy &enemy)
{
    // check if enemy has valid tile id
    if (enemy.p_tileId == -1)
    {
        enemy.p_tileId = mgr_tile->GetPathStart().p_id;
    }

    PrintDebug(enemy.p_tileId, "Enemy new id");
    // get tile
    Tile tile = mgr_tile->GetTile(enemy.p_tileId);

    // update data
    enemy.p_position = tile.p_position;
    enemy.p_dirty = false;

    PrintDebug("enemy has been cleaned", "Update Test");
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
    enemy.p_speed = 1;
    m_enemies.push_back(enemy);
}
