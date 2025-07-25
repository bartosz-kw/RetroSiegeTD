#include <vector>
#include "../structs/enemy.hpp"

class TileManager;
class EnemyManager
{
    private:
    std::vector<Enemy> m_enemies = {};
    TileManager* mgr_tile = nullptr;
    private:
    const uint16_t GetEnemyTextureIndex(uint16_t typeId) const;
    public:
    void Update(float deltaTime);
    void Draw(uint8_t screenOffset) const;
    void InjectDependencies(TileManager* mgr_tilePtr);
    void Init();

};