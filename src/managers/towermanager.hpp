#pragma once
#include <vector>
#include "../structs/tower.hpp"

class TileManager; 
class Tile;
class EnemyManager;
class BulletManager; 

class TowerManager
{
private:
    std::vector<Tower> m_towers = {};
    Tower* m_lastSelectedTower = nullptr;
    TileManager* mgr_tile = nullptr; 
    EnemyManager* mgr_enemy = nullptr;
    BulletManager* mgr_bullet = nullptr; 
private:
    void DetectInput();
    void DetectTowerInput(Tower& tower);
    void UpdateFight(Tower& tower, float deltatime);
public:
    TowerManager() = default;

    Vector2 GetCenterPosition(const Tower& tower) const; 
    uint16_t GetTowerTextureIndex(uint16_t typeId) const;
    void AddTower(Tower tower);
    void RemoveTower(int32_t id);
    Tower* GetLastSelectedTower();
    bool CanPlaceTower(Tile *tile);
    void Update(float deltaTime);
    void Draw(uint8_t screenOffset) const;
    void Init();
    void InjectDependencies(TileManager* mgr_tilePtr, EnemyManager* mgr_enemyPtr, BulletManager* mgr_bulletPtr);    
};