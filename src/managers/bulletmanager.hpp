#pragma once
#include <vector>
#include "../structs/bullet.hpp"

class BulletManager
{
private:
    static int32_t g_nextBulletId;
private:
    std::vector<Bullet> m_bullets = {};
private:
    uint16_t GetBulletTextureIndex(const uint16_t typeId) const;
    void UpdatePosition(Bullet& bullet,const float deltaTime);
    void ValidatePosition(Bullet& bullet);
    void RemoveBullets();
public:
    static int32_t GetNewValidId();
public:
    BulletManager() = default;

    std::vector<Bullet*> GetBulletsFromArea(const Rectangle area);
    void AddBullet(const Bullet bullet);
    void Update(const float deltaTime);
    void Draw(const uint8_t screenOffset) const;
    void Init();
};
