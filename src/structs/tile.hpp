#pragma once
#include <cstdint>
#include <raylib.h>
struct Tile
{
    Vector2 p_position = {0,0};
    uint16_t p_id = -1;
    uint16_t p_typeId = 0;

    // if p_nextTileId = 0 then its not a path tile 
    // Start of the path
    // -1 = Up
    // -2 = Down
    // -3 = Right
    // -4 = Left
    // End
    // -5 = End
    // Direction codes:
    // 1 = Up
    // 2 = Down
    // 3 = Right
    // 4 = Left
    int16_t p_moveDirection = -1;
};