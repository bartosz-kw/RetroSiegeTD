#pragma once
#include <vector>
#include "../structs/tower.hpp"

class TileManager; // Forward declaration for tile and manager
class Tile;

class TowerManager
{
private:
    std::vector<Tower> m_towers = {};
    TileManager* mgr_tile = nullptr; // Add dependency pointer

public:
    TowerManager() = default;

    uint16_t GetTowerTextureIndex(uint16_t typeId) const;
    void AddTower(Tower tower);
    void RemoveTower(int32_t id);
    bool CanPlaceTower(Tile *tile);
    void DetectInput();
    void Update(float deltaTime);
    void Draw(uint8_t screenOffset) const;
    void Init();
    void InjectDependencies(TileManager* mgr_tilePtr); 
};