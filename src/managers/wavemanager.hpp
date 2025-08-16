#pragma once
#include "../structs/wave.hpp"
#include "../structs/tempmessage.hpp"

class EnemyManager;
class PSManager;

class WaveManager
{
private:
    std::vector<EnemyWave> m_unactiveWaves = {};
    std::vector<EnemyWave> m_activeWaves = {};
    TempMessage m_waveMessage = {};
    float m_time = 0.0f;
    EnemyManager *mgr_enemy = nullptr;
    PSManager *mgr_ps = nullptr;

private:
    void PreKillWave(const EnemyWave wave);
    void KillWave(const uint32_t waveId);
    void RemoveEnemySpawn(EnemyWave &wave, const size_t index);
    void RemoveUnactiveWave(const uint32_t id);
    void RemoveActiveWave(const uint32_t id);
    void UpdateUnactiveWaves();
    void UpdateActiveWaves();
    void LoadWaves();


public:
    WaveManager() = default;

    TempMessage *GetWaveMessage();
    EnemyWave *GetNextWave();
    EnemyWave *GetCurrentWave();
    void ClearActiveWaves();
    void ClearUnactiveWaves();
    void Update(const float deltaTime);
    void InjectDependencies(EnemyManager *enemyManager, PSManager *psManager);
    void Init();
};
