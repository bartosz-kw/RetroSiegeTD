#include "loading.hpp"
#include "../utility/colorutil.hpp"
#include "../structs/tile.hpp"
#include <tuple>
#include <unordered_map>
#include <cassert>

std::unordered_map<Color, int16_t, ColorHash> ColorToDirectionsMap =
{                       
    { { 0x36, 0xff, 0x00, 255 }, TileDirection::StartDown }, // 36ff00 - bright green
    { { 0xff, 0x00, 0x00, 255 }, TileDirection::End }, // ff0000 - red
    { { 0x66, 0x39, 0x31, 255 }, TileDirection::Down }, // 663931 - dark brown
    { { 0x7a, 0x3c, 0x31, 255 }, TileDirection::Right }  // 7a3c31 - brownish red
};

std::unordered_map<Color, int16_t, ColorHash> ColorTileType = 
{
    { { 0x43, 0x6e, 0x1b, 255 }, TileType::GrassTile },  // 436e1b - dark olive green
    { { 0x33, 0x6b, 0x8b, 255 }, TileType::GrassPath1 },  // 336b8b - dark blue-gray
    { { 0x2c, 0xa0, 0xe2, 255 }, TileType::GrassPath2 },   // 2ca0e2 - light azure
    { { 0x2f, 0x7c, 0xa8, 255 }, TileType::GrassPath3 },  // 2f7ca8 - steel blue
    { { 0x44, 0x66, 0x7a, 255 }, TileType::GrassPath4 }   // 44667a - muted slate blue
};

std::array<std::array<int16_t, 18>, 18> Loading::LoadMapDirections(const char *path)
{
    Image image = LoadImage(path);
    assert(image.width == 18 && image.height == 18 && "LoadMapDirections(const char* path) needs 18x18 image");
    Color *colors = LoadImageColors(image);
    std::array<std::array<int16_t, 18>, 18> directions{};
    for (int x = 0; x < 18; x++)
    {
        for (int y = 0; y < 18; y++)
        {
            Color currentColor = colors[y * 18 + x];

            auto it = ColorToDirectionsMap.find(currentColor);
            if (it != ColorToDirectionsMap.end())
            {
                directions[y][x] = it->second;
            }
            else
            {
                directions[y][x] = 0;
            }
        }
    }

    UnloadImageColors(colors);
    UnloadImage(image);

    return directions;
}

std::array<std::array<uint16_t, 18>, 18> Loading::LoadTileTypes(const char *path)
{
    Image image = LoadImage(path);
    assert(image.width == 18 && image.height == 18 && "LoadTileTypes(const char* path) needs 18x18 image");

    Color *colors = LoadImageColors(image);
    std::array<std::array<uint16_t, 18>, 18> tileTypes{};

    for (int x = 0; x < 18; x++)
    {
        for (int y = 0; y < 18; y++)
        {
            Color currentColor = colors[y * 18 + x];

            auto it = ColorTileType.find(currentColor);
            if (it != ColorTileType.end())
            {
                tileTypes[y][x] = it->second;
            }
            else
            {
                tileTypes[y][x] = 1;
            }
        }
    }

    UnloadImageColors(colors);
    UnloadImage(image);

    return tileTypes;
}