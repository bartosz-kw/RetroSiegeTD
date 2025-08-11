#pragma once
#include "../structs/wave.hpp"
#include "../structs/tempmessage.hpp"

class EnemyManager; 
class PSManager; 

class WaveManager {
private:
    std::vector<EnemyWave> m_enemyWaves = {};
    TempMessage m_waveMessage = {};
    float m_time = 0.0f;
    EnemyManager* mgr_enemy = nullptr; 
    PSManager* mgr_ps = nullptr;

private:
    void PreKillWave(EnemyWave* wave);
    void RemoveWave(const uint32_t id);
    void HandleWave();
    void LoadWaves();
public:
    WaveManager() = default;

    
    TempMessage* GetWaveMessage();
    EnemyWave* GetSmallestIdWave();
    void ClearWaves();
    void Update(const float deltaTime);
    void InjectDependencies(EnemyManager* enemyManager, PSManager* psManager);
    void Init();
};
