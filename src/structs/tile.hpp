#pragma once
#include <cstdint>
#include <raylib.h>
struct Tile
{
    Vector2 p_position = {0,0};
    uint16_t p_id = 0;
    uint16_t p_typeId = 0;
    // if p_nextTileId = -3 then its not a path tile 
    // if p_nextTileId = -2 end of the path
    // if p_nextTileId = -1 start of the path
    int16_t p_nextTileId = -3;
};