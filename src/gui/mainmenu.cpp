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
    ;
    titleLabel.p_text = "Untitled Tower Defense";
    titleLabel.p_updateFunction = [](float deltaTime, TextLabel &label) {};
    titleLabel.p_rect = {static_cast<float>(Settings::g_boundingSize), 0, 270.0f, 75.0f};
    titleLabel.p_textPosition = {0, 0};
    titleLabel.p_color = WHITE;
    titleLabel.p_id = 0;
    titleLabel.p_visible = true;
    titleLabel.p_menuElement = true;

#pragma endregion
}

void MainMenu::InitButtons()
{
    constexpr size_t amountOfButtons = 1;
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
    startButton.p_rect = {0, 0, 100, 30};
    startButton.p_textPosition = {0, 0};
    startButton.p_imagePosition = {0, 0};
    startButton.p_color = BLUE;
    startButton.p_id = 0;
    startButton.p_isHovered = false;
    startButton.p_visible = true;
    startButton.p_menuElement = true;
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
