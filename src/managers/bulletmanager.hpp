#pragma once
#include <vector>
#include "../structs/bullet.hpp"

class BulletManager
{
private:
    std::vector<Bullet> m_bullets = {};

    uint16_t GetBulletTextureIndex(uint16_t typeId) const;
private:
    void UpdatePosition(Bullet& bullet,float deltaTime);
    void ValidatePosition(Bullet& bullet);
    void RemoveBullets();
public:
    BulletManager() = default;

    std::vector<Bullet> CheckHitAtPosition(const Rectangle area);
    void AddBullet(Bullet bullet);
    void Update(float deltaTime);
    void Draw(uint8_t screenOffset) const;
    void Init();
};
