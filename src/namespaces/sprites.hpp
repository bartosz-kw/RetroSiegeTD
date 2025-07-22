#include <raylib.h>

namespace Sprites
{
    inline Texture2D g_grassTile = {0};

    void LoadTextures()
    {
        g_grassTile = LoadTexture("src/resources/sprites/GrassTile.png");

    }
    void UnLoadTextures()
    {
        UnloadTexture(g_grassTile);
    }
}