#pragma once
#include <vector>
#include "../structs/gamemap.hpp"
#include "../structs/tile.hpp"
class TileManager
{
private:
    inline static const uint8_t g_tileSize = 15;
    std::vector<Tile> m_tiles = {};

private:
    const uint16_t GetTileTextureIndex(uint16_t typeId) const;

public:
    TileManager() = default;
    ~TileManager() = default;
    void Draw() const;
    void LoadMap(GameMap gameMap);
    void Init();
};
