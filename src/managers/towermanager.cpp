#include "towermanager.hpp"
#include "../utility/debugUtil.hpp"
#include "../namespaces/towers.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/bullets.hpp"
#include "../namespaces/basics.hpp"
#include "../namespaces/music.hpp"
#include "../namespaces/settings.hpp"
#include "../managers/psmanager.hpp"
#include "../managers/tilemanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/bulletmanager.hpp"
#include "../managers/particlemanager.hpp"
#include <cassert>
#include <cmath>
#include <algorithm>


int32_t g_nextValidId = 1;

// Private

std::vector<Tower>::iterator TowerManager::TryGetTowerIterator(const int32_t id)
{
    std::vector<Tower>::iterator it = std::lower_bound(m_towers.begin(), m_towers.end(),id, [](Tower tower, const int32_t id)
    { return tower.p_id < id; });
    return it;
}

int32_t TowerManager::GetNextValidId()
{
    return g_nextValidId++;
}
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
            tower.p_id = static_cast<int32_t>(GetNextValidId());
            tower.p_tileId = tile->p_id;
            tower.p_dirty = true;
            AddTower(tower);
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

    float range = tower.p_rangeless ? 9999.9f : tower.p_range;
    Vector2 centerPos = GetCenterPosition(tower);
    uint32_t enemyId = mgr_enemy->FindEnemyInArea(centerPos, range);

    if (enemyId == 0 || tower.p_timeToAttack < tower.p_attackSpeed)
    {
        return;
    }
    Enemy *enemy = mgr_enemy->GetEnemyById(enemyId);
    if (enemy)
    {
        tower.p_fightFunction(deltatime, &tower, enemy, mgr_enemy, mgr_bullet, this, mgr_ps, mgr_particle);
    }
    tower.p_timeToAttack = 0.0f;
}
void TowerManager::UpdateAnimation(Tower &tower, const float deltaTime)
{
    Basics::Animate(deltaTime, tower);
}

// Public

std::string TowerManager::TowerTypeToString(const TowerType type)
{
    switch (type)
    {
    case TowerType::Nothing:
        return "Nothing";
        break;
    case TowerType::NinjaLv1:
    case TowerType::NinjaLv2:
    case TowerType::NinjaLv3:
    case TowerType::NinjaLv4:
        return "Ninja";
        break;
    case TowerType::KnightLv1:
    case TowerType::KnightLv2:
    case TowerType::KnightLv3:
    case TowerType::KnightLv4:
    case TowerType::KnightLv5:
        return "Knight";
        break;
    case TowerType::MarketLv1:
    case TowerType::MarketLv2:
    case TowerType::MarketLv3:
    case TowerType::MarketLv4:
        return "Market";
        break;
    default:
        return "Unknown";
        break;
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
bool TowerManager::WasAnyTowerPlaced() const
{
    return m_wasAnyTowerPlaced;
}
void TowerManager::AddTower(const Tower tower)
{
    m_towers.push_back(tower);
    m_wasAnyTowerPlaced = true;
}
void TowerManager::RemoveTower(const int32_t id)
{
    m_towers.erase
    (
        std::remove_if(m_towers.begin(),m_towers.end(),[id](const Tower& tower)
        {
            return id == tower.p_id;
        })
    );
}
Tower *TowerManager::GetLastSelectedTower()
{
    return GetTowerById(m_lastSelectedTowerId);
}
Tower *TowerManager::GetTowerById(const int32_t id)
{
    std::vector<Tower>::iterator it = TryGetTowerIterator(id);
    if (it == m_towers.end())
    {
        return nullptr;
    }
    if (it->p_id == id)
    {
        return &(*it);
    }
    return nullptr;
}
size_t TowerManager::GetTowerIndexById(const int32_t id)
{
    std::vector<Tower>::iterator it = TryGetTowerIterator(id);
    if (it == m_towers.end())
    {
        return static_cast<size_t>(-1);;
    }
        if (it->p_id == id)
    {
        return it - m_towers.begin();
    }
    return static_cast<size_t>(-1);;
}
const Tower *TowerManager::GetReadTowerById(const int32_t id) const
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
const size_t TowerManager::GetTowerCount() const
{
    return m_towers.size();
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
        UpdateAnimation(tower, deltaTime);
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

        Texture2D texture = Sprites::g_textures[GetTowerTextureIndex(tower.p_typeId)];
        Rectangle dest = {floorf(tower.p_position.x + screenOffset), floorf(tower.p_position.y), static_cast<float>(tower.p_sourceRect.width), static_cast<float>(tower.p_sourceRect.height)};
        DrawTexturePro(texture, tower.p_sourceRect, dest, {0, 0}, 0.0f, WHITE);
    }
    DrawHover(screenOffset);
    if (m_lastSelectedTowerId != -1)
    {
        const Tower *tower = GetReadTowerById(m_lastSelectedTowerId);
        if (!tower)
        {
            return;
        }

        const Color color = {0, 121, 241, 128};
        const Vector2 centerPos = GetCenterPosition(*tower);
        DrawCircle(
            static_cast<int>(centerPos.x + screenOffset),
            static_cast<int>(centerPos.y),
            static_cast<float>(tower->p_range),
            color);
    }
}
void TowerManager::InjectDependencies(TileManager *mgr_tilePtr, EnemyManager *mgr_enemyPtr, BulletManager *mgr_bulletPtr, PSManager *mgr_psPtr, ParticleManager *mgr_particlePtr)
{
    mgr_tile = mgr_tilePtr;
    mgr_enemy = mgr_enemyPtr;
    mgr_bullet = mgr_bulletPtr;
    mgr_ps = mgr_psPtr;
    mgr_particle = mgr_particlePtr;
}
void TowerManager::Init()
{
    assert(mgr_tile != nullptr && "TileManager wasn't injected and its dependency");
    assert(mgr_enemy != nullptr && "EnemyManager wasn't injected and its dependency");
    assert(mgr_bullet != nullptr && "BulletManager wasn't injected and its dependency");
    assert(mgr_ps != nullptr && "PSManager wasn't injected and its dependency");
    assert(mgr_particle != nullptr && "ParticleManager wasn't injected and its dependency");
}
