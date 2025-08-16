#include "wavemanager.hpp"
#include "enemymanager.hpp"
#include "psmanager.hpp"
#include "../namespaces/enemies.hpp"
#include "../utility/debugUtil.hpp"
#include <cassert>

// Private

void WaveManager::PreKillWave(const EnemyWave wave)
{
    m_waveMessage = {};
    m_waveMessage.p_message = "Cleared: $" + std::to_string(wave.p_moneyReward) + "+";
    m_waveMessage.p_time = 3.0f;
    mgr_ps->AddMoney(wave.p_moneyReward);
}
void WaveManager::KillWave(const uint32_t waveId)
{
    for (EnemyWave &wave : m_activeWaves)
    {
        if (wave.p_id == waveId)
        {
            PreKillWave(wave);
            RemoveActiveWave(waveId);
            return;
        }
    }
}
void WaveManager::RemoveEnemySpawn(EnemyWave &wave, const size_t index)
{
    if (index < wave.p_enemySpawns.size())
    {
        wave.p_enemySpawns.erase(wave.p_enemySpawns.begin() + index);
    }
}
void WaveManager::ActivateWave(EnemyWave *wave)
{
    if (wave)
    {
        m_activeWaves.push_back(*wave);
        RemoveUnactiveWave(wave->p_id);
    }
}
void WaveManager::RemoveUnactiveWave(const uint32_t id)
{
    const auto eraseLambda = [id](const EnemyWave &wave)
    {
        return wave.p_id == id;
    };
    m_unactiveWaves.erase(std::remove_if(m_unactiveWaves.begin(), m_unactiveWaves.end(), eraseLambda), m_unactiveWaves.end());
}
void WaveManager::RemoveActiveWave(const uint32_t id)
{
    const auto eraseLambda = [id](const EnemyWave &wave)
    {
        return wave.p_id == id;
    };
    m_activeWaves.erase(std::remove_if(m_activeWaves.begin(), m_activeWaves.end(), eraseLambda), m_activeWaves.end());
}
void WaveManager::UpdateUnactiveWaves()
{
    if (!m_activeWaves.empty())
    {
        return;
    }

    EnemyWave *nextWave = GetNextWave();
    ActivateWave(nextWave);
}
void WaveManager::UpdateActiveWaves()
{
    if (m_activeWaves.empty())
    {
        return;
    }

    int indexToDelete = -1;
    for (EnemyWave &wave : m_activeWaves)
    {
        for (size_t i = 0; i < wave.p_enemySpawns.size(); i++)
        {
            if (wave.p_enemySpawns[i].first < m_time)
            {
                Enemy enemy = Enemies::GetEnemyData(wave.p_enemySpawns[i].second);
                enemy.p_tileId = -1;
                enemy.p_id = mgr_enemy->GetNewValidId();
                mgr_enemy->AddEnemy(enemy);
                m_time = 0.0f;
                indexToDelete = i;
                break;
            }
        }
        if (indexToDelete != -1)
        {
            RemoveEnemySpawn(wave, indexToDelete);
        }
        if (wave.p_enemySpawns.empty() && mgr_enemy->IsEnemiesEmpty())
        {
            KillWave(wave.p_id);
            return;
        }
    }
}
void WaveManager::LoadWaves()
{
    std::vector<std::pair<float, int>> enemySpawns2 = {};
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns2.push_back({2.0f, EnemyType::RedSlime});
    EnemyWave wave2 = {};
    wave2.p_id = 2;
    wave2.p_moneyReward = 50;
    wave2.p_enemySpawns = enemySpawns2;

    std::vector<std::pair<float, int>> enemySpawns1 = {};
    enemySpawns1.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns1.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns1.push_back({1.0f, EnemyType::BlueSlime});
    EnemyWave wave1 = {};
    wave1.p_id = 1;
    wave1.p_moneyReward = 40;
    wave1.p_enemySpawns = enemySpawns1;
    m_unactiveWaves.push_back(wave1);
    m_unactiveWaves.push_back(wave2);
}

// Public
TempMessage *WaveManager::GetWaveMessage()
{
    TempMessage *result = &m_waveMessage;
    if (m_waveMessage.p_time <= 0)
    {
        m_waveMessage = {};
    }

    return result;
}
EnemyWave *WaveManager::GetNextWave()
{
    if (m_unactiveWaves.empty())
        return nullptr;

    EnemyWave *smallest = &m_unactiveWaves[0];
    for (auto &wave : m_unactiveWaves)
    {
        if (wave.p_id < smallest->p_id)
        {
            smallest = &wave;
        }
    }
    return smallest;
}
EnemyWave *WaveManager::GetCurrentWave()
{
    if (m_activeWaves.empty())
        return nullptr;

    EnemyWave *smallest = &m_activeWaves[0];
    for (auto &wave : m_activeWaves)
    {
        if (wave.p_id < smallest->p_id)
        {
            smallest = &wave;
        }
    }
    return smallest;
}
void WaveManager::SkipWave()
{
    EnemyWave *nextWave = GetNextWave();
    ActivateWave(nextWave);
}
void WaveManager::ClearActiveWaves()
{
    m_activeWaves.clear();
}
void WaveManager::ClearUnactiveWaves()
{
    m_unactiveWaves.clear();
}
void WaveManager::Update(const float deltaTime)
{
    assert(mgr_enemy != nullptr && "enemyManager wasn't injected and its dependency");

    m_time += deltaTime;
    UpdateUnactiveWaves();
    UpdateActiveWaves();
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
};