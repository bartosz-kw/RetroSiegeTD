#include <cstddef>
#include "../utility/debugUtil.hpp"
#include "../namespaces/sprites.hpp"
#include "game.hpp"
void Game::UpdateDebug()
{
    #ifdef RELEASE
        return;
    #endif

        if (IsKeyPressed(KEY_F11))
    {
        ToggleBorderlessWindowed();
    }
}
void Game::Update()
{
    UpdateDebug();
}
void Game::MakeTextureFrame() const
{
    BeginTextureMode(m_frame);
    ClearBackground(BLACK);

    for (size_t i = 0; i < 18; i++)
    {
        for (size_t j = 0; j < 18; j++)
        {
            DrawTextureV(Sprites::g_grassTile, {15.0f * i, 15.0f * j}, WHITE);
        }
    }

    EndTextureMode();
}
void Game::Draw() const
{
    MakeTextureFrame();
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(
        m_frame.texture,
        {0, 0, static_cast<float>(p_gameHeight), static_cast<float>(-p_gameHeight)},
        {420, 0, static_cast<float>(p_scaledWidth), static_cast<float>(p_scaledHeight)},
        {0, 0},
        0.0f,
        WHITE);

    constexpr int boundingWidth = 420;
    DrawRectangle(0, 0, boundingWidth, p_scaledHeight, GRAY);
    DrawRectangle(p_scaledWidth + boundingWidth, 0, boundingWidth, p_scaledHeight, GRAY);

    EndDrawing();
}
void Game::Init()
{
    InitWindow(p_screenWidth, p_screenHeight, "Sigma Game");
    ToggleBorderlessWindowed();
    SetExitKey(KEY_F12);
    SetTargetFPS(120);
    Sprites::LoadTextures();
    m_mainFont = LoadFont(R"(src\resources\fonts\VT323-Regular.ttf)");
    m_frame = LoadRenderTexture(p_gameWidth, p_gameHeight);
}
void Game::Run()
{
    while (!WindowShouldClose())
    {
        if (IsWindowMinimized())
        {
            return;
        }

        Update();
        Draw();
    }
}
void Game::Shutdown()
{
    Sprites::UnLoadTextures();
    UnloadRenderTexture(m_frame);
    CloseWindow();
}