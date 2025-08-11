#include "playermanager.hpp"
#include "../managers/psmanager.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/enemymanager.hpp"
#include <cassert>

bool PlayerManager::IsGameOver() const
{   
    return mgr_ps->IsAlive();
}

void PlayerManager::InjectDependencies(PSManager* psManager, TowerManager* towerManager, EnemyManager* enemyManager)
{
    mgr_ps = psManager;
    mgr_tower = towerManager;
    mgr_enemy = enemyManager;
}

void PlayerManager::Init()
{
    assert(mgr_ps != nullptr && "PSManager dependency not injected");
    assert(mgr_tower != nullptr && "TowerManager dependency not injected");
    assert(mgr_enemy != nullptr && "EnemyManager dependency not injected");
}

