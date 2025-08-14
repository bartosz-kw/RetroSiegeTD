#include "../structs/tower.hpp"
class PSManager;


namespace Basics
{
    void UpgradeTower(const float deltaTime, Tower *tower, PSManager *mgr_ps, const TowerType upgradeType);
}