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
    void Animate(const float deltaTime, Enemy &enemy,uint16_t frameOffset,uint16_t frameAmount)
    {
        enemy.p_timePassed += deltaTime;
        if (enemy.p_timePassed >= enemy.p_timeToNextFrame)
        {
            enemy.p_timePassed = 0.0f;
            if (enemy.p_sourceRect.x + frameOffset > frameOffset * (frameAmount - 1))
            {
                enemy.p_sourceRect = {0, 0,static_cast<float>(frameOffset),enemy.p_sourceRect.height};
            }
            else
            {
                enemy.p_sourceRect.x += frameOffset;
            }
        }
    };
}