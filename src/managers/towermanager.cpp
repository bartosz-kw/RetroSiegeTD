#include "towermanager.hpp"
#include "../utility/debugUtil.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/settings.hpp"
#include "../managers/tilemanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/bulletmanager.hpp"
#include <cassert>
#include <algorithm>

constexpr float centerOffset = 7.5f; // since all textures are 15x15

Vector2 TowerManager::GetCenterPosition(const Tower& tower) const
{
    return Vector2{tower.p_position.x + centerOffset,tower.p_position.y + centerOffset};
}
void TowerManager::InjectDependencies(TileManager *mgr_tilePtr, EnemyManager *mgr_enemyPtr, BulletManager *mgr_bulletPtr)
{
    mgr_tile = mgr_tilePtr;
    mgr_enemy = mgr_enemyPtr;
    mgr_bullet = mgr_bulletPtr;
}
uint16_t TowerManager::GetTowerTextureIndex(uint16_t typeId) const
{
    return typeId + Sprites::towerTextureOffset;
}
void TowerManager::AddTower(Tower tower)
{
    m_towers.push_back(tower);
}
void TowerManager::RemoveTower(int32_t id)
{
    m_towers.erase(
        std::remove_if(m_towers.begin(), m_towers.end(),
                       [id](const Tower &t)
                       { return t.p_id == id; }),
        m_towers.end());
}
bool TowerManager::CanPlaceTower(Tile *tile)
{
    if (tile->p_moveDirection != 0)
    {
        return false;
    }
    for (auto &tower : m_towers)
    {
        if (tower.p_tileId == tile->p_id)
            return false;
    }
    return true;
}
void TowerManager::DetectInput()
{
    if (IsKeyDown(KEY_T))
    {
        Tile *tile = mgr_tile->GetLastClickedTile();
        if (tile == nullptr)
            return;
        if (!CanPlaceTower(tile))
            return;

        Tower tower = {};
        tower.p_typeId = TowerType::Ninja;
        tower.p_id = static_cast<int32_t>(m_towers.size() + 1);
        tower.p_tileId = tile->p_id;
        tower.p_dirty = true;
        PrintDebug(tile->p_id,"Tower Placed At");
        AddTower(tower);
    }
}
void TowerManager::Update(float deltaTime)
{
    assert(mgr_tile && "mgr_tile in towermanager was nullptr");
    assert(mgr_enemy && "mgr_enemy in towermanager was nullptr");
    assert(mgr_bullet && "mgr_bullet in towermanager was nullptr");

    DetectInput();

    for (auto &tower : m_towers)
    {
        Vector2 centerPos = GetCenterPosition(tower);
        uint32_t enemyId = mgr_enemy->FindEnemyInArea(centerPos,tower.p_range);
        // TODO: enemy damage logic


        if (!tower.p_dirty)
            continue;

        // Get the tile from TileManager and update tower position
        Tile tile = mgr_tile->GetTile(tower.p_tileId);
        tower.p_position = tile.p_position;
        tower.p_dirty = false;
    }
}
void TowerManager::Draw(uint8_t screenOffset) const
{
    for (auto &tower : m_towers)
    {
        DrawTexture
        (
            Sprites::g_textures[GetTowerTextureIndex(tower.p_typeId)],
            tower.p_position.x + screenOffset,
            tower.p_position.y,
            WHITE
        );
        if(Settings::debugView)
        {
            Color color = {255,0,0,125};
            Vector2 centerPos = GetCenterPosition(tower);     
            DrawCircle
            (
                static_cast<int>(centerPos.x + screenOffset),
                static_cast<int>(centerPos.y ),
                static_cast<float>(tower.p_range),
                color
            );
        }
    }
}
void TowerManager::Init()
{
    Tower tower = {};
    tower.p_typeId = TowerType::Ninja;
    tower.p_id = 1;
    tower.p_tileId = 40;
    tower.p_range = 60;
    AddTower(tower);
}