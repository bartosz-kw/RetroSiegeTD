#include <vector>
#include "../structs/enemy.hpp"

class TileManager;
class EnemyManager
{
private:
    std::vector<Enemy> m_enemies = {};
    TileManager *mgr_tile = nullptr;

private:
    const uint16_t GetEnemyTextureIndex(uint16_t typeId) const;

public:
    Vector2 GetCenterPosition(const Enemy& enemy) const; // Add this line
    uint32_t FindEnemyInArea(Vector2 center, float radius);
    Enemy* GetEnemyById(uint32_t id);
    void UpdateMovement(Enemy &enemy, float deltaTime);
    void CleanEnemy(Enemy &enemy);
    void RemoveEnemies();
    void Update(float deltaTime);
    void Draw(uint8_t screenOffset) const;
    void InjectDependencies(TileManager *mgr_tilePtr);
    void Init();
};