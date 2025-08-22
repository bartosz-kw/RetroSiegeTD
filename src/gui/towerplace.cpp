#include "towerplace.hpp"
#include "../namespaces/sprites.hpp"
#include "../namespaces/settings.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/guimanager.hpp"
#include <format>
#include <cassert>

void TowerPlace::InitLabels()
{
    constexpr size_t amountOfLabels = 1;
    mgr_gui->ReserveLabel(amountOfLabels);

#pragma region HeaderLabel
    TextLabel &headerLabel = mgr_gui->AddLabel(TextLabel{});
    headerLabel.p_rect = {static_cast<float>(Settings::g_boundingSize + 270.0f + 5.0f), 3.0f, static_cast<float>(Settings::g_boundingSize - 10), 20.0f};
    headerLabel.p_id = mgr_gui->GetAmountOfLabels();
    headerLabel.p_text = "Towers: ";
    headerLabel.p_color = YELLOW;
#pragma endregion
}

void TowerPlace::ControlPlaceTower(const TowerType controlType)
{
    if (mgr_tower->GetPlaceTower() == controlType)
    {
        mgr_tower->SetPlaceTower(TowerType::Nothing);
    }
    else
    {
        mgr_tower->SetPlaceTower(controlType);
    }
}

void TowerPlace::InitButtons()
{
    constexpr size_t amountOfButtons = 2;
    mgr_gui->ReserveButton(amountOfButtons);

#pragma region NinjaButton
    Button &ninjaButton = mgr_gui->AddButton(Button{});
    ninjaButton.p_text = "";
    ninjaButton.p_rect = {static_cast<float>(Settings::g_boundingSize + 270.0f + 5.0f), 25.0f, 25.0f, 25.0f};
    ninjaButton.p_color = YELLOW;
    ninjaButton.p_id = mgr_gui->GetAmountOfButtons();
    ninjaButton.p_isHovered = false;
    ninjaButton.p_visible = true;
    ninjaButton.p_buttonImage = Sprites::g_textures[Sprites::g_towerTextureOffset + TowerType::NinjaLv1];
    ninjaButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        ControlPlaceTower(TowerType::NinjaLv1);
    };
    ninjaButton.p_updateFunction = [this](float deltaTime, Button &button)
    {
        if (this->mgr_tower->GetPlaceTower() == TowerType::NinjaLv1)
        {
            button.p_color = {202, 199, 0, 255};
        }
        else
        {
            button.p_color = YELLOW;
        }
    };
#pragma endregion

#pragma region KnightButton
    Button &knightButton = mgr_gui->AddButton(Button{});
    knightButton.p_text = "";
    knightButton.p_rect = {static_cast<float>(Settings::g_boundingSize + 270.0f + 5.0f + 30.0f), 25.0f, 25.0f, 25.0f};
    knightButton.p_color = YELLOW;
    knightButton.p_id = mgr_gui->GetAmountOfButtons();
    knightButton.p_isHovered = false;
    knightButton.p_visible = true;
    knightButton.p_buttonImage = Sprites::g_textures[Sprites::g_towerTextureOffset + TowerType::KnightLv1];
    knightButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        ControlPlaceTower(TowerType::KnightLv1);
    };
    knightButton.p_updateFunction = [this](float deltaTime, Button &button)
    {
        if (this->mgr_tower->GetPlaceTower() == TowerType::KnightLv1)
        {
            button.p_color = {202, 199, 0, 255};
        }
        else
        {
            button.p_color = YELLOW;
        }
    };
#pragma endregion
}
void TowerPlace::InjectDependencies(TowerManager *towerManager, GuiManager *guiManager)
{
    mgr_tower = towerManager;
    mgr_gui = guiManager;
}
void TowerPlace::Init()
{
    assert(mgr_tower != nullptr && "TowerManager wasn't injected and its dependency");
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
    InitButtons();
}
