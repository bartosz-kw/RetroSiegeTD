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
    TileManager* mgr_tile = nullptr; 
    EnemyManager* mgr_enemy = nullptr;
    BulletManager* mgr_bullet = nullptr; 
public:
    TowerManager() = default;

    Vector2 GetCenterPosition(const Tower& tower) const; 
    uint16_t GetTowerTextureIndex(uint16_t typeId) const;
    void AddTower(Tower tower);
    void RemoveTower(int32_t id);
    bool CanPlaceTower(Tile *tile);
    void DetectInput();
    void UpdateFight(Tower& tower, float deltatime);
    void Update(float deltaTime);
    void Draw(uint8_t screenOffset) const;
    void Init();
    void InjectDependencies(TileManager* mgr_tilePtr, EnemyManager* mgr_enemyPtr, BulletManager* mgr_bulletPtr);

    
};