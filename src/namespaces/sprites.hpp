#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <raylib.h>

namespace Sprites
{
    extern const int8_t g_tileTextureOffset;
    extern const uint8_t g_tileTextures;
    extern const uint8_t g_enemyTextures;
    extern const uint8_t g_towerTextures;
    extern const uint8_t g_bulletTextures;
    extern const uint8_t g_guiTextures;
    extern const uint8_t g_enemyTextureOffset;
    extern const uint8_t g_towerTextureOffset;
    extern const uint8_t g_bulletTextureOffset;
    extern const uint8_t g_guiTextureOffset;

    inline constexpr size_t g_textureAmount = 39;
    extern std::array<Texture2D, g_textureAmount> g_textures;

    void LoadTextures();
    void UnloadTextures();
}
