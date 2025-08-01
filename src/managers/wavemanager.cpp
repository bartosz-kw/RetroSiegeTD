#include "wavemanager.hpp"
#include "enemymanager.hpp"
#include "../namespaces/enemies.hpp"
#include "../utility/debugUtil.hpp"

void WaveManager::HandleWave()
{
    if (m_time >= 5.0f)
    {
        Enemy enemy = Enemies::GetEnemyData(EnemyType::BlueSlime);
        enemy.p_tileId = -1;
        enemy.p_id = mgr_enemy->GetNewValidId();
        mgr_enemy->AddEnemy(enemy);
        m_time = 0.0f;
    }
}

void WaveManager::Update(float deltaTime)
{
    assert(mgr_enemy != nullptr && "enemyManager wasn't injected and its dependency");

    m_time += deltaTime;
    HandleWave();
}

void WaveManager::InjectDependencies(EnemyManager* enemyManager)
{
    mgr_enemy = enemyManager;
}

void WaveManager::Init()
{
    std::vector<std::pair<float, int>> enemySpawns = {};
    enemySpawns.push_back({10.0f,EnemyType::BlueSlime});
    enemySpawns.push_back({11.0f,EnemyType::BlueSlime});
    enemySpawns.push_back({12.0f,EnemyType::BlueSlime});
    EnemyWave wave = {};
    wave.p_id = 1;
    wave.p_enemySpawns = enemySpawns;
    m_enemyWaves.push_back(wave);

    m_time = 0.0f;
}
