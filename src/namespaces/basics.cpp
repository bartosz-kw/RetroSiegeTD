#include "basics.hpp"
#include "towers.hpp"
#include "../managers./psmanager.hpp"
#include <cassert>
namespace Basics
{
    void UpgradeTower(const float deltaTime, Tower *tower, PSManager *mgr_ps, const TowerType upgradeType)
    {
        assert(upgradeType != TowerType::Nothing);
        if (upgradeType == TowerType::Nothing)
        {
            return;
        }
        
        Tower upgradedTower = Towers::GetTowerData(upgradeType);
        if (!tower)
        {
            return;
        }

        if (mgr_ps->CanAfford(upgradedTower.p_price))
        {
            mgr_ps->SubMoney(upgradedTower.p_price);
            upgradedTower.p_id = tower->p_id;
            upgradedTower.p_tileId = tower->p_tileId;
            upgradedTower.p_dirty = true;
            *tower = upgradedTower;
        }
    }
}