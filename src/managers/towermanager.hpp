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
    TileManager* mgr_tile = nullptr; 
    EnemyManager* mgr_enemy = nullptr;
    PSManager* mgr_ps = nullptr;
    BulletManager* mgr_bullet = nullptr; 
private:
    void DetectInput();
    void DetectTowerInput(Tower& tower);
    void UpdateFight(Tower& tower, const float deltatime);
public:
    TowerManager() = default;

    std::string TowerTypeToString(const TowerType type);
    Vector2 GetCenterPosition(const Tower& tower) const; 
    uint16_t GetTowerTextureIndex(const uint16_t typeId) const;
    void AddTower(Tower tower);
    void RemoveTower(const int32_t id);
    Tower* GetLastSelectedTower();
    Tower* GetTowerById(const int32_t id);
    const Tower* GetReadTowerById(const int32_t id) const;
    TowerType GetPlaceTower() const;
    void SetPlaceTower(const TowerType type);
    bool CanPlaceTower(const Tile *tile) const;
    void ClearTowers();
    void Update(const float deltaTime);
    void DrawHover(const uint8_t screenOffset) const;
    void Draw(const uint8_t screenOffset) const;
    void InjectDependencies(TileManager* mgr_tilePtr, EnemyManager* mgr_enemyPtr, BulletManager* mgr_bulletPtr, PSManager* mgr_psPtr); 
    void Init();   
};
