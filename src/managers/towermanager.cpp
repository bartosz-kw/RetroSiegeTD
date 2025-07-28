#include "towermanager.hpp"
#include "../namespaces/sprites.hpp"
#include "../managers/tilemanager.hpp" 
#include <cassert>
#include <algorithm>

void TowerManager::InjectDependencies(TileManager* mgr_tilePtr)
{
    mgr_tile = mgr_tilePtr;
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
            [id](const Tower& t) { return t.p_id == id; }),
        m_towers.end()
    );
}
void TowerManager::DetectInput()
{
    if (IsKeyPressed(KEY_T))
    {
        Tower tower = {};
        tower.p_typeId = 1;
        tower.p_id = static_cast<int32_t>(m_towers.size() + 1);
        tower.p_tileId = 40; 
        tower.p_dirty = true;
        AddTower(tower);
    }
}
void TowerManager::Update(float deltaTime)
{
    assert(mgr_tile && "mgr_tile in towermanager was nullptr");

    DetectInput();

    for (auto& tower : m_towers)
    {
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
    }
    
}
void TowerManager::Init()
{
    Tower tower = {};
    tower.p_typeId = 1;
    tower.p_id = 1;
    tower.p_tileId = 40;
    AddTower(tower);
}