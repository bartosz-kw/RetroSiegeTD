#include "wavemanager.hpp"
#include "enemymanager.hpp"
#include "psmanager.hpp"
#include "../namespaces/enemies.hpp"
#include "../utility/debugUtil.hpp"
#include <cassert>

// Private

void WaveManager::PreKillWave(EnemyWave* wave)
{
    m_waveMessage = {};
    m_waveMessage.p_message = "Cleared: $" + std::to_string(wave->p_moneyReward) + "+";
    m_waveMessage.p_time = 3.0f;
    mgr_ps->AddMoney(wave->p_moneyReward);
}
void WaveManager::RemoveWave(const uint32_t id)
{
    const auto eraseLambda = [id](const EnemyWave &wave)
    {
        return wave.p_id == id;
    };
    m_enemyWaves.erase(std::remove_if(m_enemyWaves.begin(), m_enemyWaves.end(), eraseLambda), m_enemyWaves.end());
}
void WaveManager::HandleWave()
{
    EnemyWave *currentWave = GetSmallestIdWave();
    if (!currentWave)
    {
        return;
    }

    int indexToDelete = -1;
    for (size_t i = 0; i < currentWave->p_enemySpawns.size(); i++)
    {
        if (currentWave->p_enemySpawns[i].first < m_time)
        {
            Enemy enemy = Enemies::GetEnemyData(currentWave->p_enemySpawns[i].second);
            enemy.p_tileId = -1;
            enemy.p_id = mgr_enemy->GetNewValidId();
            mgr_enemy->AddEnemy(enemy);
            m_time = 0.0f;
            // set deletion index
            indexToDelete = i;
            break;
        }
    }
    if (indexToDelete != -1)
    {
        currentWave->p_enemySpawns.erase(currentWave->p_enemySpawns.begin() + indexToDelete);
    }
    if (currentWave->p_enemySpawns.empty() && mgr_enemy->IsEnemiesEmpty())
    {
        
        PreKillWave(currentWave);
        RemoveWave(currentWave->p_id);
        // PrintDebugError(currentWave->p_id); // funny undefined behavior
        return; // safe guard, ending function after deleting used pointer
    }
}
void WaveManager::LoadWaves()
{
    std::vector<std::pair<float, int>> enemySpawns2 = {};
    enemySpawns2.push_back({2.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({2.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    EnemyWave wave2 = {};
    wave2.p_id = 2;
    wave2.p_moneyReward = 50;
    wave2.p_enemySpawns = enemySpawns2;

    std::vector<std::pair<float, int>> enemySpawns1 = {};
    enemySpawns1.push_back({5.0f, EnemyType::BlueSlime});
    enemySpawns1.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns1.push_back({1.0f, EnemyType::BlueSlime});
    EnemyWave wave1 = {};
    wave1.p_id = 1;
    wave1.p_moneyReward = 40;
    wave1.p_enemySpawns = enemySpawns1;
    m_enemyWaves.push_back(wave1);
    m_enemyWaves.push_back(wave2);
}

// Public
TempMessage* WaveManager::GetWaveMessage()
{
    TempMessage* result = &m_waveMessage;
    if (m_waveMessage.p_time <= 0)
    {
        m_waveMessage = {};
    }
    
    return result;
}
EnemyWave *WaveManager::GetSmallestIdWave()
{
    if (m_enemyWaves.empty())
        return nullptr;

    EnemyWave *smallest = &m_enemyWaves[0];
    for (auto &wave : m_enemyWaves)
    {
        if (wave.p_id < smallest->p_id)
        {
            smallest = &wave;
        }
    }
    return smallest;
}
void WaveManager::ClearWavesVector()
{
    m_enemyWaves.clear();
}
void WaveManager::Update(const float deltaTime)
{
    assert(mgr_enemy != nullptr && "enemyManager wasn't injected and its dependency");

    m_time += deltaTime;
    HandleWave();
}
void WaveManager::InjectDependencies(EnemyManager *enemyManager, PSManager *psManager)
{
    mgr_enemy = enemyManager;
    mgr_ps = psManager;
}
void WaveManager::Init()
{
    LoadWaves();

    m_time = 0.0f;
}


