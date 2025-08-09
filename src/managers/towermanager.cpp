#include "towermanager.hpp"
#include "../utility/debugUtil.hpp"
#include "../namespaces/towers.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/bullets.hpp"
#include "../namespaces/settings.hpp"
#include "../managers/psmanager.hpp"
#include "../managers/tilemanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/bulletmanager.hpp"
#include <cassert>
#include <cmath>
#include <algorithm>

// Private

void TowerManager::DetectInput()
{

    // this is debug key, and this will be changed in later versions
    if (IsKeyDown(KEY_T))
    {
        if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return;
        }
        
        Tile *tile = mgr_tile->GetLastClickedTile();
        if (tile == nullptr)
            return;
        if (!CanPlaceTower(tile))
            return;

        Tower tower = Towers::GetTowerData(TowerType::NinjaLv1);
        if (tower.p_price <= mgr_ps->GetMoney())
        {
            mgr_ps->SubMoney(tower.p_price);
            tower.p_id = static_cast<int32_t>(m_towers.size() + 1);
            tower.p_tileId = tile->p_id;
            tower.p_dirty = true;
            AddTower(tower);
        }
    }
}
void TowerManager::DetectTowerInput(Tower &tower)
{
    Vector2 mousePosition = GetMousePosition();
    Texture2D texture = Sprites::g_textures[GetTowerTextureIndex(tower.p_typeId)];
    Rectangle towerRect =
        {
            tower.p_position.x * Settings::g_gameScale + Settings::g_boundingSize * Settings::g_gameScale // x
            ,
            tower.p_position.y * Settings::g_gameScale // y
            ,
            static_cast<float>(texture.width * Settings::g_gameScale) // width
            ,
            static_cast<float>(texture.height * Settings::g_gameScale) // height
        };

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }
    if (!CheckCollisionPointRec(mousePosition, towerRect))
    {
        return;
    }
    if (tower.p_dirty)
    {
        return;
    }

    m_lastSelectedTowerId = tower.p_id;
}
void TowerManager::UpdateFight(Tower &tower, float deltatime)
{
    tower.p_timeToAttack += deltatime;

    Vector2 centerPos = GetCenterPosition(tower);
    uint32_t enemyId = mgr_enemy->FindEnemyInArea(centerPos, tower.p_range);

    if (enemyId == 0 || tower.p_timeToAttack < tower.p_attackSpeed)
    {
        return;
    }
    Enemy *enemy = mgr_enemy->GetEnemyById(enemyId);
    if (enemy)
    {
        tower.p_fightFunction(deltatime,&tower,enemy,mgr_enemy,mgr_bullet,this);
    }
    tower.p_timeToAttack = 0.0f;
}

// Public

std::string TowerManager::TowerTypeToString(TowerType type)
{
    switch (type)
    {
    case TowerType::NinjaLv1:
        return "Ninja";
    default:
        return "Unknown";
    }
}
Vector2 TowerManager::GetCenterPosition(const Tower &tower) const
{
    Texture2D towerTexture = Sprites::g_textures[GetTowerTextureIndex(tower.p_typeId)];
    return Vector2{tower.p_position.x + towerTexture.width / 2.0f, tower.p_position.y + towerTexture.height / 2.0f};
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
Tower *TowerManager::GetLastSelectedTower()
{
    return GetTowerById(m_lastSelectedTowerId);
}
Tower *TowerManager::GetTowerById(int32_t id)
{
    for (auto &tower : m_towers)
    {
        if (tower.p_id == id)
        {
            return &tower;
        }
    }
    return nullptr;
}
bool TowerManager::CanPlaceTower(Tile *tile) const
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
void TowerManager::Update(float deltaTime)
{
    assert(mgr_tile && "mgr_tile in towermanager was nullptr");
    assert(mgr_enemy && "mgr_enemy in towermanager was nullptr");
    assert(mgr_bullet && "mgr_bullet in towermanager was nullptr");

    DetectInput();

    for (auto &tower : m_towers)
    {
        assert(tower.p_id >= 0 && tower.p_id <= (18 * 18));
        if (tower.p_dirty)
        {
            Tile tile = mgr_tile->GetTile(tower.p_tileId);
            assert(tile.p_id != -1);
            tower.p_position = tile.p_position;
            tower.p_dirty = false;
        }

        UpdateFight(tower, deltaTime);
        DetectTowerInput(tower);
    }
}
void TowerManager::DrawHover(uint8_t screenOffset) const
{
    Tower selectedTower = Towers::GetTowerData(1);
    Tile *lastHoveredTile = mgr_tile->GetLastHoveredTile();
    if (lastHoveredTile)
    {
        if (IsKeyDown(KEY_T) && CanPlaceTower(lastHoveredTile))
        {
            Color towerColor = {255, 255, 255, 128};
            Color rangeColor = {41, 154, 255, 128};
            DrawTexture(Sprites::g_textures[GetTowerTextureIndex(selectedTower.p_typeId)], lastHoveredTile->p_position.x + screenOffset, lastHoveredTile->p_position.y, towerColor);
            Vector2 centerPos = mgr_tile->GetTileCenterPosition(*lastHoveredTile);
            DrawCircle(
                static_cast<int>(centerPos.x + screenOffset),
                static_cast<int>(centerPos.y),
                static_cast<float>(selectedTower.p_range),
                rangeColor);
        }
    }
}
void TowerManager::Draw(uint8_t screenOffset) const
{
    for (auto &tower : m_towers)
    {
        if (tower.p_dirty)
        {
            continue;
        }
        
        DrawTexture(
            Sprites::g_textures[GetTowerTextureIndex(tower.p_typeId)],
            tower.p_position.x + screenOffset,
            tower.p_position.y,
            WHITE);
        if (Settings::g_debugView)
        {
            Color color = {255, 0, 0, 125};
            Vector2 centerPos = GetCenterPosition(tower);
            DrawCircle(
                static_cast<int>(centerPos.x + screenOffset),
                static_cast<int>(centerPos.y),
                static_cast<float>(tower.p_range),
                color);
        }
    }
    DrawHover(screenOffset);
}
void TowerManager::InjectDependencies(TileManager *mgr_tilePtr, EnemyManager *mgr_enemyPtr, BulletManager *mgr_bulletPtr, PSManager *mgr_psPtr)
{
    mgr_tile = mgr_tilePtr;
    mgr_enemy = mgr_enemyPtr;
    mgr_bullet = mgr_bulletPtr;
    mgr_ps = mgr_psPtr;
}
void TowerManager::Init()
{
    assert(mgr_tile != nullptr && "TileManager wasn't injected and its dependency");
    assert(mgr_enemy != nullptr && "EnemyManager wasn't injected and its dependency");
    assert(mgr_bullet != nullptr && "BulletManager wasn't injected and its dependency");
    assert(mgr_ps != nullptr && "PSManager wasn't injected and its dependency");
}
