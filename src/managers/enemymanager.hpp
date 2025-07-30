#include <vector>
#include "../structs/enemy.hpp"

class TileManager;
class BulletManager;

class EnemyManager
{
private:
    std::vector<Enemy> m_enemies = {};
    TileManager *mgr_tile = nullptr;
    BulletManager *mgr_bullet = nullptr;

private:
    const uint16_t GetEnemyTextureIndex(uint16_t typeId) const;
    Vector2 CalculateMovePosition(int16_t moveDirection);

public:
    Vector2 GetCenterPosition(const Enemy& enemy) const; 
    uint32_t FindEnemyInArea(Vector2 center, float radius);
    Enemy* GetEnemyById(uint32_t id);
    void UpdateVisualPosition(Enemy &enemy, Vector2& tilePosition,int16_t moveDirection);
    void UpdateMovement(Enemy &enemy, float deltaTime);
    void HandleHits(Enemy &enemy);
    void CleanEnemy(Enemy &enemy);
    void RemoveEnemies();
    void Update(float deltaTime);
    void Draw(uint8_t screenOffset) const;
    void InjectDependencies(TileManager *mgr_tilePtr, BulletManager *mgr_bulletPtr);
    void Init();
};
