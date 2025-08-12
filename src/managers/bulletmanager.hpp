#pragma once
#include <vector>
#include "../structs/bullet.hpp"

class BulletManager
{
private:
    std::vector<Bullet> m_bullets = {};

    uint16_t GetBulletTextureIndex(const uint16_t typeId) const;
private:
    void UpdatePosition(Bullet& bullet,const float deltaTime);
    void ValidatePosition(Bullet& bullet);
    void RemoveBullets();
public:
    BulletManager() = default;

    std::vector<Bullet*> GetBulletsFromArea(const Rectangle area);
    void AddBullet(const Bullet bullet);
    void Update(const float deltaTime);
    void Draw(const uint8_t screenOffset) const;
    void Init();
};
