#pragma once
#include <memory>

class PSManager;
class TowerManager;
class EnemyManager;

class PlayerManager
{
private:
    PSManager *mgr_ps = nullptr;
    TowerManager *mgr_tower = nullptr;
    EnemyManager *mgr_enemy = nullptr;

public:
    PlayerManager() = default;
    ~PlayerManager() = default;

    bool IsGameOver() const;
    void InjectDependencies(PSManager *psManager, TowerManager *towerManager, EnemyManager *enemyManager);
    void Init();
};
