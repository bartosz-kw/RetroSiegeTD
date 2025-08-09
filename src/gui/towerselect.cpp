#include "towerselect.hpp"
#include "../namespaces/settings.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/guimanager.hpp"
#include <format>
#include <cassert>

constexpr uint16_t startingPoint = 250;
constexpr uint8_t offset = 15;
constexpr int8_t gap = -10;

void TowerSelect::InitLabels()
{
    constexpr size_t amountOfLabels = 5;
    mgr_gui->ReserveLabel(amountOfLabels);

    TextLabel &nameLabel = mgr_gui->AddLabel(TextLabel{});
    nameLabel.p_text = "";
    nameLabel.p_id = mgr_gui->GetAmountOfLabels();
    nameLabel.p_fontSize = Settings::g_gameFont.baseSize;
    nameLabel.p_rect = {5, (startingPoint - offset * 4) + gap * 5, 95, 20};
    nameLabel.p_color = BLUE;
    nameLabel.p_updateFunction = [this](float deltaTime,TextLabel &label)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            label.p_visible = false;
            return;
        }
        label.p_text = "Id: " + std::to_string(tower->p_id) + "/ Type: " +
                       this->mgr_tower->TowerTypeToString(static_cast<TowerType>(tower->p_typeId));
        label.p_visible = true;
    };

    TextLabel &levelLabel = mgr_gui->AddLabel(TextLabel{});
    levelLabel.p_text = "";
    levelLabel.p_id = mgr_gui->GetAmountOfLabels();
    levelLabel.p_fontSize = Settings::g_gameFont.baseSize;
    levelLabel.p_rect = {5, (startingPoint - offset * 3) + gap * 4, 58, 20};
    levelLabel.p_color = BLUE;
    levelLabel.p_updateFunction = [this](float deltaTime,TextLabel &label)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            label.p_visible = false;
            return;
        }
        label.p_text = "Lv: " + std::to_string(tower->p_level);
        label.p_visible = true;
    };

    TextLabel &damageLabel = mgr_gui->AddLabel(TextLabel{});
    damageLabel.p_text = "";
    damageLabel.p_id = mgr_gui->GetAmountOfLabels();
    damageLabel.p_fontSize = Settings::g_gameFont.baseSize;
    damageLabel.p_rect = {5, (startingPoint - offset * 2) + gap * 3, 58, 20};
    damageLabel.p_color = BLUE;
    damageLabel.p_updateFunction = [this](float deltaTime,TextLabel &label)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            label.p_visible = false;
            return;
        }
        label.p_text = "Dmg: " + std::to_string(tower->p_damage);
        label.p_visible = true;
    };

    TextLabel &attackSpeedLabel = mgr_gui->AddLabel(TextLabel{});
    attackSpeedLabel.p_text = "";
    attackSpeedLabel.p_id = mgr_gui->GetAmountOfLabels();
    attackSpeedLabel.p_fontSize = Settings::g_gameFont.baseSize;
    attackSpeedLabel.p_rect = {5, (startingPoint - offset * 1) + gap * 2, 58, 20};
    attackSpeedLabel.p_color = BLUE;
    attackSpeedLabel.p_updateFunction = [this](float deltaTime,TextLabel &label)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            label.p_visible = false;
            return;
        }
        label.p_text = "As: " + std::format("{:.2f}", tower->p_attackSpeed);
        label.p_visible = true;
    };

    TextLabel &rangeLabel = mgr_gui->AddLabel(TextLabel{});
    rangeLabel.p_text = "R: 0";
    rangeLabel.p_id = mgr_gui->GetAmountOfLabels();
    rangeLabel.p_fontSize = Settings::g_gameFont.baseSize / 1.0f;
    rangeLabel.p_rect = {5, (startingPoint - offset * 0) + gap * 1, 58, 20};
    rangeLabel.p_color = BLUE;
    rangeLabel.p_updateFunction = [this](float deltaTime,TextLabel &label)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            label.p_visible = false;
            return;
        }
        label.p_text = "R: " + std::format("{:.2f}", tower->p_range);
        label.p_visible = true;
    };
}
void TowerSelect::InitButtons()
{
    constexpr size_t amountOfButtons = 1;
    mgr_gui->ReserveButton(amountOfButtons);

    Button &upgradeButton = mgr_gui->AddButton(Button{});
    upgradeButton.p_text = "Upg";
    upgradeButton.p_id = mgr_gui->GetAmountOfButtons();
    upgradeButton.p_rect = {65, (startingPoint - offset * 0) + gap * 1, 36, 20};
    upgradeButton.p_color = GREEN;
    upgradeButton.p_fontSize = Settings::g_gameFont.baseSize;
    upgradeButton.p_updateFunction = [this](float deltaTime,Button &button)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            button.p_visible = false;
            return;
        }
        button.p_visible = true;
    };
    upgradeButton.p_onPressed = [this](float deltaTime,Button &button)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        if (tower)
        {
            PrintDebug("Hello world"); 
        }
    };
}
void TowerSelect::InjectDependencies(TowerManager *towerManager, GuiManager *guiManager)
{
    mgr_tower = towerManager;
    mgr_gui = guiManager;
}
void TowerSelect::Init()
{
    assert(mgr_tower != nullptr && "TowerManager wasn't injected and its dependency");
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
    InitButtons();
}
