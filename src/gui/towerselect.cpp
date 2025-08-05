#include "towerselect.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/guimanager.hpp"
#include <format>
#include <cassert>

void TowerSelect::UpdateTextPosition(TextLabel& label)
{
    Vector2 textMeasurement = MeasureTextEx(GetFontDefault(), label.p_text.c_str(), GetFontDefault().baseSize, 1.0f);
    label.p_textPosition = {
        label.p_rect.x + label.p_rect.width / 2.0f - textMeasurement.x / 2.0f,
        label.p_rect.y + label.p_rect.height / 2.0f - textMeasurement.y / 2.0f
    };
}
void TowerSelect::UpdateTextPosition(Button& button)
{
    Vector2 textMeasurement = MeasureTextEx(GetFontDefault(), button.p_text.c_str(), GetFontDefault().baseSize, 1.0f);
    button.p_textPosition = {
        button.p_rect.x + button.p_rect.width / 2.0f - textMeasurement.x / 2.0f,
        button.p_rect.y + button.p_rect.height / 2.0f - textMeasurement.y / 2.0f
    };
}
void TowerSelect::InitLabels()
{
    constexpr uint8_t amountOfLabels = 5;
    mgr_gui->ReserveLabel(amountOfLabels);

    TextLabel& nameLabel = mgr_gui->AddLabel(TextLabel{});
    nameLabel.p_text = "";
    nameLabel.p_id = 1;
    nameLabel.p_fontSize = GetFontDefault().baseSize;
    nameLabel.p_rect = {0, 170, 105, 20};
    nameLabel.p_color = BLUE;
    nameLabel.p_updateFunction = [&nameLabel, this]()
    {
        
        Tower* tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            nameLabel.p_visible = false;
            return;
        }
        nameLabel.p_text = "Id: " + std::to_string(tower->p_id) + "/ Type: " + this->mgr_tower->TowerTypeToString((TowerType)tower->p_typeId);;
        nameLabel.p_visible = true;
        
    };


    TextLabel& levelLabel = mgr_gui->AddLabel(TextLabel{});
    levelLabel.p_text = "";
    levelLabel.p_id = 1;
    levelLabel.p_fontSize = GetFontDefault().baseSize;
    levelLabel.p_rect = {0, 190, 63, 20};
    levelLabel.p_color = BLUE;
    levelLabel.p_updateFunction = [&levelLabel, this]()
    {
        Tower* tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            levelLabel.p_visible = false;
            return;
        }
        levelLabel.p_text = "L: " + std::to_string(tower->p_level);
        levelLabel.p_visible = true;
        
    };

    TextLabel& damageLabel = mgr_gui->AddLabel(TextLabel{});
    damageLabel.p_text = "";
    damageLabel.p_id = 2;
    damageLabel.p_fontSize = GetFontDefault().baseSize;
    damageLabel.p_rect = {0, 210, 63, 20};
    damageLabel.p_color = BLUE;
    damageLabel.p_updateFunction = [&damageLabel, this]()
    {
        Tower* tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            damageLabel.p_visible = false;
            return;
        }
        damageLabel.p_text = "D: " + std::to_string(tower->p_damage);
        damageLabel.p_visible = true;
    };

    TextLabel& attackSpeedLabel = mgr_gui->AddLabel(TextLabel{});
    attackSpeedLabel.p_text = "";
    attackSpeedLabel.p_id = 3;
    attackSpeedLabel.p_fontSize = GetFontDefault().baseSize;
    attackSpeedLabel.p_rect = {0, 230, 63, 20};
    attackSpeedLabel.p_color = BLUE;
    attackSpeedLabel.p_updateFunction = [&attackSpeedLabel, this]()
    {
        Tower* tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            attackSpeedLabel.p_visible = false;
            return;
        }
        attackSpeedLabel.p_text = "AS: " + std::format("{:.2f}", tower->p_attackSpeed);
        attackSpeedLabel.p_visible = true;
    };

    TextLabel& rangeLabel = mgr_gui->AddLabel(TextLabel{});
    rangeLabel.p_text = "R: 0";
    rangeLabel.p_id = 4;
    rangeLabel.p_fontSize = GetFontDefault().baseSize;
    rangeLabel.p_rect = {0, 250, 63, 20};
    rangeLabel.p_color = BLUE;
    rangeLabel.p_updateFunction = [&rangeLabel, this]()
    {
        Tower* tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            rangeLabel.p_visible = false;
            return;
        }
        rangeLabel.p_text = "R: " + std::format("{:.2f}", tower->p_range);
        rangeLabel.p_visible = true;
    };
}
void TowerSelect::InitButtons()
{
    constexpr uint8_t amountOfButtons = 1;
    mgr_gui->ReserveButton(amountOfButtons);

    
    Button& upgradeButton = mgr_gui->AddButton(Button{});
    upgradeButton.p_text = "Upgrade";
    upgradeButton.p_id = 1;
    upgradeButton.p_rect = {63, 250, 42, 20};
    upgradeButton.p_color = GREEN;
    upgradeButton.p_fontSize = GetFontDefault().baseSize;
    upgradeButton.p_updateFunction = [&upgradeButton, this]()
    {
        Tower* tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            upgradeButton.p_visible = false;
            return;
        }
        upgradeButton.p_visible = true;
    };
    upgradeButton.p_onPressed = [this]()
    {
        Tower* tower = this->mgr_tower->GetLastSelectedTower();
        if (tower)
        {
            PrintDebug("Hello world");//this->mgr_tower->UpgradeTower(tower->p_id);
        }
    };
}
void TowerSelect::InjectDependencies(TowerManager* towerManager,GuiManager* guiManager)
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
