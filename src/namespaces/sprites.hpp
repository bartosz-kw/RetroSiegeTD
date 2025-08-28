#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <raylib.h>

namespace Sprites
{
    inline constexpr int8_t g_tileTextureOffset = -1;
    inline constexpr uint8_t g_tileTextures = 5;
    inline constexpr uint8_t g_enemyTextures = 5;
    inline constexpr uint8_t g_towerTextures = 9;
    inline constexpr uint8_t g_bulletTextures = 7;
    inline constexpr uint8_t g_guiTextures = 3;
    inline constexpr uint8_t g_enemyTextureOffset = g_tileTextureOffset + g_tileTextures;
    inline constexpr uint8_t g_towerTextureOffset = g_enemyTextureOffset + g_enemyTextures;
    inline constexpr uint8_t g_bulletTextureOffset = g_towerTextureOffset + g_towerTextures;
    inline constexpr uint8_t g_guiTextureOffset = g_bulletTextureOffset + g_bulletTextures;
    
    inline constexpr size_t g_textureAmount = 29;
    inline std::array<Texture2D, g_textureAmount> g_textures = {};

    inline void LoadTextures()
    {
        g_textures[0] = LoadTexture("src/resources/sprites/GrassTile.png");
        g_textures[1] = LoadTexture("src/resources/sprites/GrassPathSprite1.png");
        g_textures[2] = LoadTexture("src/resources/sprites/GrassPathSprite2.png");
        g_textures[3] = LoadTexture("src/resources/sprites/GrassPathSprite3.png");
        g_textures[4] = LoadTexture("src/resources/sprites/GrassPathSprite4.png");
        g_textures[5] = LoadTexture("src/resources/sprites/BlueSlimeEnemy.png");
        g_textures[6] = LoadTexture("src/resources/sprites/RedSlimeEnemy.png");
        g_textures[7] = LoadTexture("src/resources/sprites/ZombieEnemy.png");
        g_textures[8] = LoadTexture("src/resources/sprites/ArmoredZombieEnemy.png");
        g_textures[9] = LoadTexture("src/resources/sprites/SkeletonEnemy.png");
        g_textures[10] = LoadTexture("src/resources/sprites/NinjaTower1.png");
        g_textures[11] = LoadTexture("src/resources/sprites/NinjaTower2.png");
        g_textures[12] = LoadTexture("src/resources/sprites/NinjaTower3.png");
        g_textures[13] = LoadTexture("src/resources/sprites/NinjaTower4.png");
        g_textures[14] = LoadTexture("src/resources/sprites/KnightTower1.png");
        g_textures[15] = LoadTexture("src/resources/sprites/KnightTower2.png");
        g_textures[16] = LoadTexture("src/resources/sprites/KnightTower3.png");
        g_textures[17] = LoadTexture("src/resources/sprites/KnightTower4.png");
        g_textures[18] = LoadTexture("src/resources/sprites/KnightTower5.png");
        g_textures[19] = LoadTexture("src/resources/sprites/ShulikenBullet.png");
        g_textures[20] = LoadTexture("src/resources/sprites/SharpShulikenBullet.png");
        g_textures[21] = LoadTexture("src/resources/sprites/DaggerBullet.png");
        g_textures[22] = LoadTexture("src/resources/sprites/SlashBullet.png");
        g_textures[23] = LoadTexture("src/resources/sprites/SpearSlashBullet.png");
        g_textures[24] = LoadTexture("src/resources/sprites/BigSlashBullet.png");
        g_textures[25] = LoadTexture("src/resources/sprites/BiggestSlashBullet.png");
        g_textures[26] = LoadTexture("src/resources/sprites/MusicOn.png");
        g_textures[27] = LoadTexture("src/resources/sprites/MusicOff.png");
        g_textures[28] = LoadTexture("src/resources/sprites/RetroSiegeTD.png");

        for (size_t i = 0; i < g_textures.size(); i++)
        {
            SetTextureFilter(g_textures[i],TEXTURE_FILTER_POINT);
        }
    }
    inline void UnloadTextures()
    {
        for (size_t i = 0; i < g_textures.size(); i++)
        {
            UnloadTexture(g_textures[i]);
        }
    }
}