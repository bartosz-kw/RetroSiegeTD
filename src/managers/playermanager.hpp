#pragma once
#include <memory>

class PSManager;
class TowerManager;
class EnemyManager;
class WaveManager;

class PlayerManager
{
private:
    PSManager *mgr_ps = nullptr;
    TowerManager *mgr_tower = nullptr;
    EnemyManager *mgr_enemy = nullptr;
    WaveManager *mgr_wave = nullptr;

public:
    PlayerManager() = default;
    ~PlayerManager() = default;

    void OnGameOver();
    bool IsGameOver() const;
    void Update();
    void InjectDependencies(PSManager *psManager, TowerManager *towerManager, EnemyManager *enemyManager, WaveManager *waveManager);
    void Init();
};
