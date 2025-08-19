#include "../structs/tower.hpp"
#include "../structs/enemy.hpp"
#include "../structs/bullet.hpp"
class PSManager;


namespace Basics
{
    void UpgradeTower(const float deltaTime, Tower *tower, PSManager *mgr_ps);
    void Animate(const float deltaTime, Enemy &enemy);
    void Animate(const float deltaTime, Bullet &bullet);
    void Animate(const float deltaTime, Tower &tower);
}
