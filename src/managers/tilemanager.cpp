#include <algorithm>
#include <cassert>
#include "../namespaces/sprites.hpp"
#include "../namespaces/settings.hpp"
#include "../utility/debugUtil.hpp"
#include "tilemanager.hpp"

const uint16_t TileManager::GetTileTextureIndex(uint16_t typeId) const
{
    return typeId + Sprites::tileTextureOffset;
}
Tile TileManager::GetPathStart()
{
    if (m_startPathId == -1)
    {
        for (auto &tile : m_tiles)
        {
            if (tile.p_moveDirection <= -1 && tile.p_moveDirection >= -4)
            {
                m_startPathId = static_cast<float>(tile.p_id);
                return tile;
            };
        }
    }
    else
    {
        return GetTile(m_startPathId);
    }
    assert(false && "getpathstart did not find the tile");
    return Tile{};
}
Tile TileManager::GetTile(uint16_t id) const
{
    auto it = std::lower_bound(m_tiles.begin(), m_tiles.end(), id, [](const Tile &tile, uint16_t id)
                               { return tile.p_id < id; });
    if (it != m_tiles.end() && it->p_id == id)
    {
        return *it;
    }

    return Tile{};
}
int16_t TileManager::GetMovedId(uint16_t tileid, int8_t direction) const
{
    direction = std::abs(direction);
    if (direction == 1)
    {
        tileid -= 18;
    }
    else if (direction == 2)
    {
        tileid += 18;
    }
    else if (direction == 3)
    {
        tileid += 1;
    }
    else if (direction == 4)
    {
        tileid += -1;
    }
    else
    {
        PrintDebugError(direction,"UNKNOWN DIRECTION");
        assert(false && "unknown direction was inputed into GetMovedId");
    }
    if (tileid < 0 || tileid > (18*18))
    {
        assert(false && "outofbounds id in GetMovedId");
        tileid = 0;
    }
    //PrintDebug(tileid);
    return tileid;
}
Tile* TileManager::GetLastClickedTile()
{
    return m_lastClickedTile;
}
bool TileManager::IsTileClicked(const Tile& tile) const
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return false;
    }
    Vector2 mousePosition = GetMousePosition();
    // TODO: Remove magic numbers
    if (!CheckCollisionPointRec(mousePosition, {tile.p_position.x * 4 + 105 * 4, tile.p_position.y * 4, 15 * 4, 15 * 4}))
    {
        return false;
    }
    return true;
}
void TileManager::Update()
{
    for (auto &tile : m_tiles)
    {
        if (IsTileClicked(tile))
        {
            m_lastClickedTile = &tile;
            PrintDebug(tile.p_id);
        }
    }
}
void TileManager::Draw(uint8_t screenOffset) const
{
    for (auto &&tile : m_tiles)
    {
        Color color = WHITE;
        if (Settings::debugView && tile.p_moveDirection != 0)
        {
            color = RED;
        }
        DrawTexture(Sprites::g_textures[GetTileTextureIndex(tile.p_typeId)], tile.p_position.x + screenOffset, tile.p_position.y, color);
    }
}
void TileManager::LoadMap(GameMap gameMap)
{
    uint16_t id = 0;
    for (size_t y = 0; y < gameMap.p_tileIdMap.size(); y++)
    {
        for (size_t x = 0; x < gameMap.p_tileIdMap[y].size(); x++)
        {
            Tile tile = {};
            tile.p_id = id;
            tile.p_typeId = gameMap.p_tileIdMap[y][x];
            tile.p_position = {static_cast<float>(g_tileSize * x), static_cast<float>(g_tileSize * y)};
            tile.p_moveDirection = gameMap.p_pathDirections[y][x];
            // PrintDebug(tile.p_typeId);
            m_tiles.push_back(tile);
            id++;
        }
    }
}
void TileManager::Init()
{
    
}

