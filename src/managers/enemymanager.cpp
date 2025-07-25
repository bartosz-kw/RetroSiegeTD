#include "enemymanager.hpp"
#include "tilemanager.hpp"
#include "../utility/debugUtil.hpp"
#include "../namespaces/sprites.hpp"
#include <cassert>

const uint16_t EnemyManager::GetEnemyTextureIndex(uint16_t typeId) const
{
    return typeId + Sprites::enemyTextureOffset;
}
void EnemyManager::Update(float deltaTime)
{
    for (auto &enemy : m_enemies)
    {
        if(!enemy.p_dirty) continue; 
        Tile tile = mgr_tile->GetTile(enemy.p_tileId);
        enemy.p_position = tile.p_position;
        enemy.p_dirty = false;
        
        PrintDebug("enemy has been cleaned","Update Test");
        assert(tile.p_id != -1);
    }
}

void EnemyManager::Draw(uint8_t screenOffset) const
{
    for (auto &enemy : m_enemies)
    {
        DrawTexture(Sprites::g_textures[GetEnemyTextureIndex(enemy.p_typeId)]
        ,enemy.p_position.x + screenOffset,enemy.p_position.y,WHITE);
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
    enemy.p_tileId = 1;
    enemy.p_typeId = 1;
    m_enemies.push_back(enemy);
}