#pragma once
#include <vector>
#include "../structs/gamemap.hpp"
#include "../structs/tile.hpp"
class TileManager
{
private:
    inline static const uint8_t g_tileSize = 15;

private:
    std::vector<Tile> m_tiles = {};
    int16_t m_startPathId = -1;

private:
    const uint16_t GetTileTextureIndex(uint16_t typeId) const;

public:
    TileManager() = default;
    ~TileManager() = default;
    Tile GetPathStart();
    Tile GetTile(uint16_t id) const;
    int16_t GetMovedId(uint16_t tileid, int8_t direction) const;
    void Update();
    void Draw(uint8_t screenOffset) const;
    void LoadMap(GameMap gameMap);
    void Init();
};
