#pragma once
#include <vector>
#include <string>
#include "../structs/tower.hpp"

class TileManager; 
class Tile;
class EnemyManager;
class BulletManager; 

class TowerManager
{
private:
    std::vector<Tower> m_towers = {};
    int32_t m_lastSelectedTowerId = -1;
    TileManager* mgr_tile = nullptr; 
    EnemyManager* mgr_enemy = nullptr;
    BulletManager* mgr_bullet = nullptr; 
private:
    void DetectInput();
    void DetectTowerInput(Tower& tower);
    void UpdateFight(Tower& tower, float deltatime);
public:
    TowerManager() = default;

    std::string TowerTypeToString(TowerType type);
    Vector2 GetCenterPosition(const Tower& tower) const; 
    uint16_t GetTowerTextureIndex(uint16_t typeId) const;
    void AddTower(Tower tower);
    void RemoveTower(int32_t id);
    Tower* GetLastSelectedTower();
    Tower* GetTowerById(int32_t id);
    bool CanPlaceTower(Tile *tile);
    void Update(float deltaTime);
    void Draw(uint8_t screenOffset) const;
    void InjectDependencies(TileManager* mgr_tilePtr, EnemyManager* mgr_enemyPtr, BulletManager* mgr_bulletPtr); 
    void Init();   
};
