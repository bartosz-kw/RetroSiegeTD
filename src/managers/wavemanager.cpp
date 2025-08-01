#include "wavemanager.hpp"
#include "enemymanager.hpp"
#include "../namespaces/enemies.hpp"
#include "../utility/debugUtil.hpp"

void WaveManager::Update(float deltaTime)
{
    assert(mgr_enemy != nullptr && "enemyManager wasn't injected and its dependency");

    m_time += deltaTime;
    PrintDebug(m_time);
    if (m_time >= 5.0f)
    {
        Enemy enemy = Enemies::GetEnemyData(EnemyType::BlueSlime);
        enemy.p_tileId = -1;
        enemy.p_id = mgr_enemy->GetNewValidId();
        mgr_enemy->AddEnemy(enemy);
        m_time = 0.0f;
    }
    
}

void WaveManager::InjectDependencies(EnemyManager* enemyManager)
{
    mgr_enemy = enemyManager;
}

void WaveManager::Init()
{
    m_time = 0.0f;
}


