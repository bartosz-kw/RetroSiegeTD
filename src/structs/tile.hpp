#pragma once
#include <cstdint>
#include <raylib.h>
enum TileDirection
{
    NoDirection = 0,

    StartUp = -1,
    StartDown = -2,
    StartRight = -3,
    StartLeft = -4,
    End = -5,
    
    Up = 1,
    Down = 2,
    Right = 3,
    Left = 4
};
enum TileType
{
    GrassTile = 1,
    GrassPath1 = 2,
    GrassPath2 = 3,
};
struct Tile
{
    Vector2 p_position = {0,0};
    int16_t p_moveDirection = TileDirection::NoDirection;
    uint16_t p_id = -1;
    uint16_t p_typeId = 0;
};