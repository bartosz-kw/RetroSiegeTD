#include "../structs/tower.hpp"
#include "../structs/enemy.hpp"
class PSManager;


namespace Basics
{
    void UpgradeTower(const float deltaTime, Tower *tower, PSManager *mgr_ps, const TowerType upgradeType);
    void Animate(const float deltaTime, Enemy &enemy,uint16_t frameOffset,uint16_t frameAmount);
}