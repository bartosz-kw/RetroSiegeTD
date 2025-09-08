#pragma once
#include <vector>
#include <string>
#include "../structs/tower.hpp"

class Tile;

class TileManager;
class EnemyManager;
class PSManager;
class BulletManager;

class TowerManager
{
private:
    std::vector<Tower> m_towers = {};
    int32_t m_lastSelectedTowerId = -1;
    TowerType m_placeTower = TowerType::Nothing;
    TileManager *mgr_tile = nullptr;
    EnemyManager *mgr_enemy = nullptr;
    PSManager *mgr_ps = nullptr;
    BulletManager *mgr_bullet = nullptr;
    ParticleManager *mgr_particle = nullptr;
    bool m_wasAnyTowerPlaced = false;

private:

    std::vector<Tower>::iterator TryGetTowerIterator(const int32_t id);
    void DetectInput();
    uint16_t GetTowerTypeAmount(const TowerType type) const;
    void DetectTowerInput(Tower &tower);
    void UpdateFight(Tower &tower, const float deltatime);
    void UpdateAnimation(Tower &tower, const float deltaTime);

public:
    TowerManager() = default;

    std::string TowerTypeToString(const TowerType type);
    Vector2 GetCenterPosition(const Tower &tower) const;
    uint16_t GetTowerTextureIndex(const uint16_t typeId) const;
    bool WasAnyTowerPlaced() const;
    void AddTower(const Tower tower);
    void RemoveTower(const int32_t id);
    Tower *GetLastSelectedTower();
    Tower *GetTowerById(const int32_t id);
    size_t GetTowerIndexById(const int32_t id);
    const Tower *GetReadTowerById(const int32_t id) const;
    const size_t GetTowerCount() const;
    int32_t GetNextValidId();
    TowerType GetPlaceTower() const;
    void SetPlaceTower(const TowerType type);
    bool CanPlaceTowerOnTile(const Tile *tile) const;
    bool ValidateTowerPlacement(const Tower& tower) const;
    void ClearTowersVector();
    void Update(const float deltaTime);
    void DrawHover(const uint8_t screenOffset) const;
    void Draw(const uint8_t screenOffset) const;
    void InjectDependencies(TileManager *mgr_tilePtr, EnemyManager *mgr_enemyPtr, BulletManager *mgr_bulletPtr, PSManager *mgr_psPtr, ParticleManager *mgr_particlePtr);
    void Init();
};
