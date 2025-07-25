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
    float deltaTime = GetFrameTime();
    UpdateDebug();
    mgr_enemy.Update(deltaTime);
}
void Game::MakeTextureFrame() const
{
    BeginTextureMode(m_frame);
    ClearBackground(BLACK);
    constexpr uint8_t boundingWidth = 105;
    constexpr uint8_t screenOffset = boundingWidth;
    constexpr Color boundingColor = BLACK;

    DrawRectangle(0, 0, boundingWidth, p_gameHeight, boundingColor);
    DrawRectangle(p_gameWidth - boundingWidth, 0, boundingWidth, p_gameHeight, boundingColor);
    mgr_tile.Draw(screenOffset);
    mgr_enemy.Draw(screenOffset);
    EndTextureMode();
}
void Game::Draw() const
{
    MakeTextureFrame();
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(
        m_frame.texture,
        {0, 0, static_cast<float>(p_gameWidth), static_cast<float>(-p_gameHeight)},
        {0, 0, static_cast<float>(p_scaledWidth), static_cast<float>(p_scaledHeight)},
        {0, 0},
        0.0f,
        WHITE);

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
    mgr_enemy.InjectDependencies(&mgr_tile);
    mgr_enemy.Init();

    GameMap map;
    map.p_id = 1;

    PrintDebug(sizeof(Tile));

    int i = 0;
    for (auto &row : map.p_tileIdMap)
    {
        row.fill(1);
        if (i == 2)
        {
            row.fill(2);
        }
        i++;
    }
    map.p_pathDirections = {{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {-3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,-5},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}};
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