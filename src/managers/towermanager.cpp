#include "towermanager.hpp"
#include "../utility/debugUtil.hpp"
#include "../namespaces/towers.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/bullets.hpp"
#include "../namespaces/music.hpp"
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
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        m_placeTower = TowerType::Nothing;
    }

    if (m_placeTower != TowerType::Nothing)
    {
        if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return;
        }

        Tile *tile = mgr_tile->GetLastClickedTile();
        Tile *hoveredTile = mgr_tile->GetCurrentHoveredTile();
        if (hoveredTile == nullptr)
            return;
        if (tile == nullptr)
            return;
        if (!CanPlaceTower(tile))
            return;
        if (tile->p_id != hoveredTile->p_id)
            return;

        Tower tower = Towers::GetTowerData(m_placeTower);
        if (mgr_ps->CanAfford(tower.p_price))
        {
            mgr_ps->SubMoney(tower.p_price);
            tower.p_id = static_cast<int32_t>(m_towers.size() + 1);
            tower.p_tileId = tile->p_id;
            tower.p_dirty = true;
            AddTower(tower);
            
            PrintDebug("SoundPlayed");
            PlaySound(GameMusic::g_towerPlaceSound);
        }
    }
}
void TowerManager::DetectTowerInput(Tower &tower)
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }

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

    if (!CheckCollisionPointRec(mousePosition, towerRect))
    {
        return;
    }
    if (tower.p_dirty)
    {
        return;
    }

    if (tower.p_id == m_lastSelectedTowerId)
    {
        m_lastSelectedTowerId = -1;
        return;
    }
    
    m_lastSelectedTowerId = tower.p_id;
}
void TowerManager::UpdateFight(Tower &tower, const float deltatime)
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
        tower.p_fightFunction(deltatime, &tower, enemy, mgr_enemy, mgr_bullet, this);
    }
    tower.p_timeToAttack = 0.0f;
}

// Public

std::string TowerManager::TowerTypeToString(const TowerType type)
{
    switch (type)
    {
    case TowerType::Nothing:
        return "Nothing";
    case TowerType::NinjaLv1:
    case TowerType::NinjaLv2:
    case TowerType::NinjaLv3:
    case TowerType::NinjaLv4:
        return "Ninja";
    case TowerType::KnightLv1:
        return "Knight";
    default:
        return "Unknown";
    }
}
Vector2 TowerManager::GetCenterPosition(const Tower &tower) const
{
    const Texture2D towerTexture = Sprites::g_textures[GetTowerTextureIndex(tower.p_typeId)];
    return Vector2{tower.p_position.x + towerTexture.width / 2.0f, tower.p_position.y + towerTexture.height / 2.0f};
}
uint16_t TowerManager::GetTowerTextureIndex(const uint16_t typeId) const
{
    return typeId + Sprites::g_towerTextureOffset;
}
void TowerManager::AddTower(const Tower tower)
{
    m_towers.push_back(tower);
}
void TowerManager::RemoveTower(const int32_t id)
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
Tower* TowerManager::GetTowerById(const int32_t id)
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
const Tower* TowerManager::GetReadTowerById(const int32_t id) const
{
    for (const auto &tower : m_towers)
    {
        if (tower.p_id == id)
        {
            return &tower;
        }
    }
    return nullptr;
}
TowerType TowerManager::GetPlaceTower() const
{
    return m_placeTower;
}
void TowerManager::SetPlaceTower(const TowerType type)
{
    m_placeTower = type;
}
bool TowerManager::CanPlaceTower(const Tile *tile) const
{
    if (tile->p_moveDirection != 0)
    {
        return false;
    }
    for (auto &tower : m_towers)
    {
        if (tower.p_tileId == tile->p_id)
        {
            return false;
        }
    }
    return true;
}
void TowerManager::ClearTowersVector()
{
    m_towers.clear();
}
void TowerManager::Update(const float deltaTime)
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
void TowerManager::DrawHover(const uint8_t screenOffset) const
{
    if (m_placeTower == TowerType::Nothing)
    {
        return;
    }
    const Tower selectedTower = Towers::GetTowerData(m_placeTower);
    const Tile *hoveredTile = mgr_tile->GetCurrentHoveredTile();
    if (hoveredTile)
    {
        if (m_placeTower != TowerType::Nothing && CanPlaceTower(hoveredTile))
        {
            const Color towerColor = {255, 255, 255, 128};
            const Color rangeColor = {41, 154, 255, 128};
            DrawTexture(Sprites::g_textures[GetTowerTextureIndex(selectedTower.p_typeId)], hoveredTile->p_position.x + screenOffset, hoveredTile->p_position.y, towerColor);
            Vector2 centerPos = mgr_tile->GetTileCenterPosition(*hoveredTile);
            DrawCircle(
                static_cast<int>(centerPos.x + screenOffset),
                static_cast<int>(centerPos.y),
                static_cast<float>(selectedTower.p_range),
                rangeColor);
        }
    }
}
void TowerManager::Draw(const uint8_t screenOffset) const
{
    for (const auto &tower : m_towers)
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
    }
    DrawHover(screenOffset);
    if (m_lastSelectedTowerId != -1)
    {
        const Tower *tower = GetReadTowerById(m_lastSelectedTowerId);
        if (!tower)
        {
            return;
        }
        
        const Color color = { 0, 121, 241, 128 };
        const Vector2 centerPos = GetCenterPosition(*tower);
        DrawCircle
        (
            static_cast<int>(centerPos.x + screenOffset),
            static_cast<int>(centerPos.y),
            static_cast<float>(tower->p_range),
            color
        );
    }
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
