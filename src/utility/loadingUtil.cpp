#include "loadingUtil.hpp"
#include <tuple>
#include <unordered_map>
#include <cassert>

bool operator==(const Color& lhs, const Color& rhs) {
    return lhs.r == rhs.r &&
           lhs.g == rhs.g &&
           lhs.b == rhs.b &&
           lhs.a == rhs.a;
}

struct ColorHash
{
    std::size_t operator()(const Color &c) const
    {
        // Combine bytes into a 32-bit integer
        return (static_cast<std::size_t>(c.r) << 24) |
               (static_cast<std::size_t>(c.g) << 16) |
               (static_cast<std::size_t>(c.b) << 8) |
               (static_cast<std::size_t>(c.a));
    }
};

std::unordered_map<Color, int16_t, ColorHash> ColorToDirectionsMap =
{                       
        {{54, 255, 0, 255}, -2}, // bright green  (36ff00)
        {{255, 0, 0, 255}, -5},  // red           (ff0000)
        {{102, 57, 49, 255}, 2}  // dark brown    (663931)
};

std::unordered_map<Color, int16_t, ColorHash> ColorTileType = 
{
    { { 0x33, 0x6b, 0x8b, 255 }, 2 },  // 336b8b - dark blue-gray
    { { 0x43, 0x6e, 0x1b, 255 }, 1 }   // 436e1b - dark olive green
};

std::array<std::array<int16_t, 18>, 18> LoadMapDirections(const char *path)
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

std::array<std::array<uint16_t, 18>, 18> LoadTileTypes(const char *path)
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