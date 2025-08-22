#include "mainmenu.hpp"
#include "../core/game.hpp"
#include "../utility/debugUtil.hpp"
#include "../namespaces/settings.hpp"
#include "../managers/guimanager.hpp"
#include <cassert>

void MainMenu::InitLabels()
{
    constexpr size_t amountOfLabels = 1;
    mgr_gui->ReserveLabel(amountOfLabels);

#pragma region TitleLabel
    TextLabel &titleLabel = mgr_gui->AddLabel(TextLabel{});
    titleLabel.p_text = "Untitled Tower Defense";
    titleLabel.p_updateFunction = [](float deltaTime, TextLabel &label) {};
    titleLabel.p_rect = {static_cast<float>(Settings::g_boundingSize), 10.0f, 270.0f, 50.0f};
    titleLabel.p_textPosition = {0, 0};
    titleLabel.p_color = BLUE;
    titleLabel.p_id = mgr_gui->GetAmountOfLabels();
    titleLabel.p_visible = true;
    titleLabel.p_menuElement = true;

#pragma endregion
}

void MainMenu::InitButtons()
{
    constexpr size_t amountOfButtons = 2;
    mgr_gui->ReserveButton(amountOfButtons);

#pragma region StartButton
    Button &startButton = mgr_gui->AddButton(Button{});
    startButton.p_text = "Play";
    startButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        if (!button.p_isHovered)
        {
            return;
        }

        mgr_game->StartGame();
    };
    startButton.p_updateFunction = [](float deltaTime, Button &button) {};
    startButton.p_buttonImage = {0, 0, 0, 0, 0};
    startButton.p_rect = {static_cast<float>(Settings::g_boundingSize) + 270.0f/2.0f - 160.0f/2.0f, 140.0f, 160.0f, 30.0f};
    startButton.p_textPosition = {0, 0};
    startButton.p_imagePosition = {0, 0};
    startButton.p_color = GREEN;
    startButton.p_id = mgr_gui->GetAmountOfButtons();
    startButton.p_isHovered = false;
    startButton.p_visible = true;
    startButton.p_menuElement = true;
#pragma endregion

#pragma region ExitButton
    Button &exitButton = mgr_gui->AddButton(Button{});
    exitButton.p_text = "Exit";
    exitButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        if (!button.p_isHovered)
        {
            return;
        }

        mgr_game->CloseGame();
    };
    exitButton.p_updateFunction = [](float deltaTime, Button &button) {};
    exitButton.p_buttonImage = {0, 0, 0, 0, 0};
    exitButton.p_rect = {static_cast<float>(Settings::g_boundingSize) + 270.0f/2.0f - 160.0f/2.0f, 180.0f, 160.0f, 30.0f};
    exitButton.p_textPosition = {0, 0};
    exitButton.p_imagePosition = {0, 0};
    exitButton.p_color = RED;
    exitButton.p_id = mgr_gui->GetAmountOfButtons();
    exitButton.p_isHovered = false;
    exitButton.p_visible = true;
    exitButton.p_menuElement = true;
#pragma endregion

}

void MainMenu::InjectDependencies(GuiManager *guiManager, Game *game)
{
    mgr_gui = guiManager;
    mgr_game = game;
}

void MainMenu::Init()
{
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
    InitButtons();
}
