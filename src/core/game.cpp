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

    mgr_tile.Draw();

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
    // managers
    mgr_tile.Init();

    GameMap map;
    map.p_id = 1;
    for (auto &row : map.p_tileIdMap)
        row.fill(1);
    mgr_tile.LoadMap(map);
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