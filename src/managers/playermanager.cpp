#include "playermanager.hpp"
#include "../managers/psmanager.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/enemymanager.hpp"
#include "../managers/wavemanager.hpp"
#include "../utility/debugUtil.hpp"
#include <cassert>

void PlayerManager::OnGameOver()
{
    mgr_enemy->ClearEnemiesVector();
    mgr_tower->ClearTowersVector();
    mgr_wave->ClearActiveWaves();
    mgr_wave->ClearUnactiveWaves();
    mgr_ps->SetMoney(0);
}

bool PlayerManager::IsGameOver() const
{
    return !mgr_ps->IsAlive();
}

PlayerState PlayerManager::GetPlayerState() const
{
    return m_playerState;
}

void PlayerManager::Update()
{
    if (!mgr_wave->GetCurrentWave() && !IsGameOver())
    {
        m_playerState = PlayerState::Victory;
    }
    else
    {
        m_playerState = IsGameOver() ? PlayerState::Dead : PlayerState::Alive;
    }
   
    if (IsGameOver())
    {
        OnGameOver();
    }
}

void PlayerManager::InjectDependencies(PSManager* psManager, TowerManager* towerManager, EnemyManager* enemyManager, WaveManager* waveManager)
{
    mgr_ps = psManager;
    mgr_tower = towerManager;
    mgr_enemy = enemyManager;
    mgr_wave = waveManager;
}

void PlayerManager::Init()
{
    assert(mgr_ps != nullptr && "PSManager dependency not injected");
    assert(mgr_tower != nullptr && "TowerManager dependency not injected");
    assert(mgr_enemy != nullptr && "EnemyManager dependency not injected");
}
