#include <cstddef>
#include "../utility/debugUtil.hpp"
#include "../utility/loadingUtil.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/settings.hpp"
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
    if (IsKeyPressed(KEY_F3))
    {
        Settings::debugView = !Settings::debugView;
    }
}
void Game::Update()
{
    float deltaTime = GetFrameTime();
    UpdateDebug();
    mgr_enemy.Update(deltaTime);
    mgr_tile.Update();
    mgr_tower.Update(deltaTime);
    mgr_bullet.Update(deltaTime);
}
void Game::MakeTextureFrame() const
{
    BeginTextureMode(m_frame);
    ClearBackground(BLACK);
    constexpr uint8_t boundingWidth = 105;
    constexpr uint8_t screenOffset = boundingWidth;
    constexpr Color boundingColor = BLACK;

    mgr_tile.Draw(screenOffset);
    mgr_enemy.Draw(screenOffset);
    mgr_tower.Draw(screenOffset);
    mgr_bullet.Draw(screenOffset);
    DrawRectangle(0, 0, boundingWidth, p_gameHeight, boundingColor);
    DrawRectangle(p_gameWidth - boundingWidth, 0, boundingWidth, p_gameHeight, boundingColor);
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
void Game::InitManagers()
{
    mgr_tile.Init();

    // loading map
    GameMap map;
    map.p_id = 1;
    map.p_tileIdMap = LoadTileTypes("src/resources/maps/Map1Tiles.png");
    map.p_pathDirections = LoadMapDirections("src/resources/maps/Map1Directions.png");
    mgr_tile.LoadMap(map);
    // continue with managers

    mgr_bullet.Init();
    mgr_enemy.InjectDependencies(&mgr_tile);
    mgr_enemy.Init();
    mgr_tower.InjectDependencies(&mgr_tile, &mgr_enemy, &mgr_bullet);
    mgr_tower.Init();
}
void Game::InitSprites()
{
    Sprites::LoadTextures();
}
void Game::InitMembers()
{
    m_mainFont = LoadFont(R"(src\resources\fonts\VT323-Regular.ttf)");
    m_frame = LoadRenderTexture(p_gameWidth, p_gameHeight);
}
void Game::InitGame()
{
    InitWindow(p_screenWidth, p_screenHeight, "Sigma Game");
    ToggleFullscreen();
    SetExitKey(KEY_NULL);
    SetTargetFPS(120);
}
void Game::Init()
{
    InitGame();
    InitSprites();
    InitMembers();
    InitManagers();
}
void Game::Run()
{
    while (!WindowShouldClose())
    {
        if (IsWindowMinimized())
        {
            continue;
        }

        Update();
        Draw();
    }
    Shutdown();
}
void Game::Shutdown()
{
    Sprites::UnLoadTextures();
    UnloadRenderTexture(m_frame);
    CloseWindow();
}