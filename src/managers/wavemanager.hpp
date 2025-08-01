#pragma once

class EnemyManager; // Forward declaration

class WaveManager {
private:
    float m_time = 0.0f;
    EnemyManager* mgr_enemy = nullptr; 
public:
    WaveManager() = default;

    
    void Update(float deltaTime);
    void InjectDependencies(EnemyManager* enemyManager);
    void Init();
};
