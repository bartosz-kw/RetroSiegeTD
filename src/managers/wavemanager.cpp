#include "wavemanager.hpp"
#include "enemymanager.hpp"
#include "../namespaces/enemies.hpp"
#include "../utility/debugUtil.hpp"

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

void WaveManager::HandleWave()
{
    EnemyWave *currentWave = GetSmallestIdWave();
    int indexToDelete = -1;
    for (size_t i = 0; i < currentWave->p_enemySpawns.size(); i++)
    {
        if (currentWave->p_enemySpawns[i].first < m_time)
        {
            Enemy enemy = Enemies::GetEnemyData(EnemyType::BlueSlime);
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
    if (currentWave->p_enemySpawns.empty())
    {
        // TODO: remove wave from list
    }
    
}
void WaveManager::Update(float deltaTime)
{
    assert(mgr_enemy != nullptr && "enemyManager wasn't injected and its dependency");

    m_time += deltaTime;
    HandleWave();
}

void WaveManager::InjectDependencies(EnemyManager *enemyManager)
{
    mgr_enemy = enemyManager;
}

void WaveManager::Init()
{
    std::vector<std::pair<float, int>> enemySpawns = {};
    enemySpawns.push_back({5.0f, EnemyType::BlueSlime});
    enemySpawns.push_back({1.0f, EnemyType::BlueSlime});
    enemySpawns.push_back({1.0f, EnemyType::BlueSlime});
    EnemyWave wave = {};
    wave.p_id = 1;
    wave.p_enemySpawns = enemySpawns;
    m_enemyWaves.push_back(wave);

    m_time = 0.0f;
}
