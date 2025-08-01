#pragma once
#include "../structs/wave.hpp"

class EnemyManager; // Forward declaration

class WaveManager {
private:
    std::vector<EnemyWave> m_enemyWaves = {};
    float m_time = 0.0f;
    EnemyManager* mgr_enemy = nullptr; 
public:
    WaveManager() = default;
        EnemyWave* GetSmallestIdWave();

    void HandleWave();
    void Update(float deltaTime);
    void InjectDependencies(EnemyManager* enemyManager);
    void Init();
};
