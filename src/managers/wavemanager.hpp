#pragma once
#include "../structs/wave.hpp"

class EnemyManager; 
class PSManager; 

class WaveManager {
private:
    std::vector<EnemyWave> m_enemyWaves = {};
    float m_time = 0.0f;
    EnemyManager* mgr_enemy = nullptr; 
    PSManager* mgr_ps = nullptr;

private:
    void PreKillWave(EnemyWave* wave);
    void RemoveWave(uint32_t id);
    void HandleWave();
    void LoadWaves();
public:
    WaveManager() = default;

    EnemyWave* GetSmallestIdWave();
    void Update(float deltaTime);
    void InjectDependencies(EnemyManager* enemyManager, PSManager* psManager);
    void Init();
};
