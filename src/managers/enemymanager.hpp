#include <vector>
#include "../structs/enemy.hpp"

class TileManager;
class BulletManager;
class PSManager;

class EnemyManager
{
private:
    std::vector<Enemy> m_enemies = {};
    Enemy* m_hoveredEnemy = nullptr;

    int32_t m_IdCounter = 1;
    
    TileManager *mgr_tile = nullptr;
    BulletManager *mgr_bullet = nullptr;
    PSManager *mgr_ps = nullptr;

private:
    const uint16_t GetEnemyTextureIndex(const uint16_t typeId) const;
    const Vector2 CalculateMovePosition(const int16_t moveDirection) const;
    void UpdateVisualPosition(Enemy &enemy, const Vector2 &tilePosition, const int16_t moveDirection);
    void UpdateMovement(Enemy &enemy, const float deltaTime);
    void UpdateHitEffect(Enemy &enemy, const float deltaTime);
    void UpdateCooldown(Enemy &enemy, const float deltaTime);
    void UpdateAnimation(Enemy &enemy, const float deltaTime);
    void UpdateEnemy(Enemy &enemy, const float deltaTime);
    void HandleHits(Enemy &enemy);
    void CheckForHover();
    void CleanEnemy(Enemy &enemy);
    void PreKillEnemy(Enemy &enemy);
    void RemoveEnemies();

public:
    bool IsEnemiesEmpty() const;
    uint32_t GetNewValidId();
    Vector2 GetCenterPosition(const Enemy &enemy) const;
    uint32_t FindEnemyInArea(const Vector2 center, const float radius);
    Enemy *GetEnemyById(const uint32_t id);
    const Enemy *GetHoveredEnemy() const;
    void AddEnemy(const Enemy enemy);
    void SpawnEnemy(const EnemyType enemy);
    void ClearEnemiesVector();
    void Update(const float deltaTime);
    void Draw(const uint8_t screenOffset) const;
    void InjectDependencies(TileManager *mgr_tilePtr, BulletManager *mgr_bulletPtr, PSManager *mgr_psPtr);
    void Init();
};
