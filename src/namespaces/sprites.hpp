#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <raylib.h>

namespace Sprites
{
    inline constexpr int8_t g_tileTextureOffset = -1;
    inline constexpr uint8_t g_tileTextures = 5;
    inline constexpr uint8_t g_enemyTextures = 7;
    inline constexpr uint8_t g_towerTextures = 13;
    inline constexpr uint8_t g_bulletTextures = 7;
    inline constexpr uint8_t g_guiTextures = 6;
    inline constexpr uint8_t g_enemyTextureOffset = g_tileTextureOffset + g_tileTextures;
    inline constexpr uint8_t g_towerTextureOffset = g_enemyTextureOffset + g_enemyTextures;
    inline constexpr uint8_t g_bulletTextureOffset = g_towerTextureOffset + g_towerTextures;
    inline constexpr uint8_t g_guiTextureOffset = g_bulletTextureOffset + g_bulletTextures;

    inline constexpr size_t g_textureAmount = 38;
    extern std::array<Texture2D, g_textureAmount> g_textures;

    void LoadTextures();
    void UnloadTextures();
}
