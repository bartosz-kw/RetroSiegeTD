#pragma once
#include <vector>
#include "../structs/bullet.hpp"

class BulletManager
{
private:
    std::vector<Bullet> m_bullets = {};

    uint16_t GetBulletTextureIndex(uint16_t typeId) const;

public:
    BulletManager() = default;

    void AddBullet(Bullet bullet);
    void RemoveBullets();

    void Update(float deltaTime);
    void Draw(uint8_t screenOffset) const;
    void Init();
};