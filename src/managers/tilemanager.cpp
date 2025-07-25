#include <algorithm>
#include "../namespaces/sprites.hpp"
#include "../utility/debugUtil.hpp"
#include "tilemanager.hpp"


const uint16_t TileManager::GetTileTextureIndex(uint16_t typeId) const
{
    return typeId + Sprites::tileTextureOffset;
}
Tile TileManager::GetTile(uint16_t id) const
{
    auto it = std::lower_bound(m_tiles.begin(),m_tiles.end(),id,[](const Tile& tile,uint16_t id)
    {
        return tile.p_id < id;
    });
    if (it != m_tiles.end() && it->p_id == id)
    {
        return *it;
    }
    
    return Tile{};
}
void TileManager::Draw(uint8_t screenOffset) const
{
    for (auto &&tile : m_tiles)
    {
        Color color = WHITE;
        if (tile.p_nextTileId != 0)
        {
            color = RED;
        }
        
        DrawTexture(Sprites::g_textures[GetTileTextureIndex(tile.p_typeId)], tile.p_position.x + screenOffset,tile.p_position.y, color);
    }
}
void TileManager::LoadMap(GameMap gameMap)
{
    uint16_t id = 0;
    for (size_t i = 0; i < gameMap.p_tileIdMap.size(); i++)
    {
        for (size_t j = 0; j < gameMap.p_tileIdMap[i].size(); j++)
        {
            Tile tile = {};
            tile.p_id = id;
            tile.p_typeId = gameMap.p_tileIdMap[i][j];
            tile.p_position = {static_cast<float>(g_tileSize * i), static_cast<float>(g_tileSize * j)};
            tile.p_nextTileId = gameMap.p_pathDirections[i][j];
            //PrintDebug(tile.p_typeId);
            m_tiles.push_back(tile);
            id++; 
        }
    }
    for (size_t i = 0; i < m_tiles.size(); i++)
    {
        PrintDebug(m_tiles[i].p_id);
    }
    
}
void TileManager::Init()
{
}