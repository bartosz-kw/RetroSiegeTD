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
    Tile* m_lastClickedTile = nullptr;
    Tile* m_currentHoveredTile = nullptr;
    Tile* m_lastHoveredTile = nullptr;
    int16_t m_startPathId = -1;
private:
    const uint16_t GetTileTextureIndex(uint16_t typeId) const;
    bool IsTileHovered(Tile& tile);
    bool IsTileClicked(Tile& tile);
public:
    TileManager() = default;
    ~TileManager() = default;
    Tile GetPathStart();
    Tile GetTile(uint16_t id) const;
    int16_t GetMovedId(uint16_t tileid, int8_t direction) const;
    Tile* GetLastClickedTile();
    Tile* GetLastHoveredTile();
    Tile* GetCurrentHoveredTile();
    Vector2 GetTileCenterPosition(const Tile& tile) const;
    void Update();
    void Draw(uint8_t screenOffset) const;
    void LoadMap(GameMap gameMap);
    void Init();
};
