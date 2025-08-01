#pragma once
#include "../structs/wave.hpp"

class EnemyManager; // Forward declaration

class WaveManager {
private:
    std::vector<EnemyWave> m_enemyWaves = {};
    float m_time = 0.0f;
    EnemyManager* mgr_enemy = nullptr; 

private:
    void RemoveWave(uint32_t id);
    void HandleWave();
    void LoadWaves();
public:
    WaveManager() = default;

    EnemyWave* GetSmallestIdWave();
    void Update(float deltaTime);
    void InjectDependencies(EnemyManager* enemyManager);
    void Init();
};
