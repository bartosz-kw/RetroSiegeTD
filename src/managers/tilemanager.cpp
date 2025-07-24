#include "../namespaces/sprites.hpp"
#include "../utility/debugUtil.hpp"
#include "tilemanager.hpp"


const uint16_t TileManager::GetTileTextureIndex(uint16_t typeId) const
{
    constexpr uint8_t indexOffset = 1;
    return typeId - indexOffset;
}
void TileManager::Draw() const
{
    for (auto &&tile : m_tiles)
    {
        DrawTextureV(Sprites::g_textures[GetTileTextureIndex(tile.p_typeId)], tile.p_position, WHITE);
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
            PrintDebug(tile.p_typeId);
            m_tiles.push_back(tile);
            id++;
        }
    }
}
void TileManager::Init()
{
}