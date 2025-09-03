#include "towerselect.hpp"
#include "../namespaces/settings.hpp"
#include "../namespaces/towers.hpp"
#include "../namespaces/basics.hpp"
#include "../utility/debugutil.hpp"
#include "../utility/colorutil.hpp"
#include "../managers/towermanager.hpp"
#include "../managers/psmanager.hpp"
#include "../managers/guimanager.hpp"
#include <format>
#include <cassert>

constexpr uint16_t startingPoint = 250;
constexpr uint8_t offset = 15;
constexpr int8_t gap = -10;

void TowerSelect::InitLabels()
{
    constexpr size_t amountOfLabels = 6;
    mgr_gui->ReserveLabel(amountOfLabels);

#pragma region BoundingLabel
    Label &boundingLabel = mgr_gui->AddLabel(Label{});
    boundingLabel.p_text = "";
    boundingLabel.p_id = mgr_gui->GetAmountOfLabels();
    boundingLabel.p_rect = {5, (startingPoint - offset * 6) + gap * 7 - 10, 95, 190};
    boundingLabel.p_color = DARKBLUE;
    boundingLabel.p_boundingSize = 2.0f;
    boundingLabel.p_boundingColor = boundingLabel.p_color * 0.8f;
    boundingLabel.p_visible = false;
    boundingLabel.p_roundness = 0.25f;
    boundingLabel.p_segments = 1.0f;
    boundingLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            label.p_visible = false;
            return;
        }
        label.p_visible = true;
    };
#pragma endregion
#pragma region NameLabel
    Label &nameLabel = mgr_gui->AddLabel(Label{});
    nameLabel.p_text = "";
    nameLabel.p_id = mgr_gui->GetAmountOfLabels();
    nameLabel.p_rect = {5, (startingPoint - offset * 6) + gap * 7, 95, 20};
    nameLabel.p_color = BLUE;
    nameLabel.p_boundingSize = 2.0f;
    nameLabel.p_boundingColor = nameLabel.p_color * 0.8f;
    nameLabel.p_visible = false;
    nameLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();
        if (!tower)
        {
            label.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                label.p_text = "Type: " + this->mgr_tower->TowerTypeToString(placeTower);
                ;
                label.p_visible = true;
            }
        }
        else
        {
            label.p_text = "Type: " + this->mgr_tower->TowerTypeToString(static_cast<TowerType>(tower->p_typeId));
            ;
            label.p_visible = true;
        }
    };
#pragma endregion
#pragma region IdLabel
    Label &IdLabel = mgr_gui->AddLabel(Label{});
    IdLabel.p_text = "";
    IdLabel.p_id = mgr_gui->GetAmountOfLabels();
    IdLabel.p_rect = {5, (startingPoint - offset * 5) + gap * 6, 95, 20};
    IdLabel.p_color = BLUE;
    IdLabel.p_boundingSize = 2.0f;
    IdLabel.p_boundingColor = IdLabel.p_color * 0.8f;
    IdLabel.p_visible = false;
    IdLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();

        if (!tower)
        {
            label.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                label.p_text = "Id: N/A";
                label.p_visible = true;
            }
        }
        else
        {
            label.p_text = "Id: " + std::to_string(tower->p_id);
            label.p_visible = true;
        }
    };
#pragma endregion
#pragma region LevelLabel
    Label &levelLabel = mgr_gui->AddLabel(Label{});
    levelLabel.p_text = "";
    levelLabel.p_id = mgr_gui->GetAmountOfLabels();
    levelLabel.p_rect = {5, (startingPoint - offset * 4) + gap * 5, 95, 20};
    levelLabel.p_color = BLUE;
    levelLabel.p_boundingSize = 2.0f;
    levelLabel.p_boundingColor = levelLabel.p_color * 0.8f;
    levelLabel.p_visible = false;
    levelLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();

        if (!tower)
        {
            label.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                const Tower tower = Towers::GetTowerData(placeTower);
                label.p_text = "Lv: " + std::to_string(tower.p_level);
                label.p_visible = true;
            }
        }
        else if (tower->p_isUpgradeHovered)
        {
            const Tower postUpgradeData = Towers::GetTowerData(tower->p_upgradesTo);
            label.p_text = "Lv: " + std::to_string(tower->p_level) + " -> " + std::to_string(postUpgradeData.p_level);
            label.p_visible = true;
        }
        else
        {
            label.p_text = "Lv: " + std::to_string(tower->p_level);
            label.p_visible = true;
        }
    };
#pragma endregion
#pragma region DamageLabel
    Label &damageLabel = mgr_gui->AddLabel(Label{});
    damageLabel.p_text = "";
    damageLabel.p_id = mgr_gui->GetAmountOfLabels();
    damageLabel.p_rect = {5, (startingPoint - offset * 3) + gap * 4, 95, 20};
    damageLabel.p_color = BLUE;
    damageLabel.p_boundingSize = 2.0f;
    damageLabel.p_boundingColor = damageLabel.p_color * 0.8f;
    damageLabel.p_visible = false;
    damageLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();
        if (!tower)
        {
            label.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                const Tower tower = Towers::GetTowerData(placeTower);
                label.p_text = "Dmg: " + std::to_string(tower.p_damage);
                label.p_visible = true;
            }
        }
        else if (tower->p_isUpgradeHovered)
        {
            const Tower postUpgradeData = Towers::GetTowerData(tower->p_upgradesTo);
            label.p_text = "Dmg: " + std::to_string(tower->p_damage) + " -> " + std::to_string(postUpgradeData.p_damage);
            ;
            label.p_visible = true;
        }
        else
        {
            label.p_text = "Dmg: " + std::to_string(tower->p_damage);

            label.p_visible = true;
        }
    };
#pragma endregion
#pragma region AttackSpeedLabel
    Label &attackSpeedLabel = mgr_gui->AddLabel(Label{});
    attackSpeedLabel.p_text = "";
    attackSpeedLabel.p_id = mgr_gui->GetAmountOfLabels();
    attackSpeedLabel.p_rect = {5, (startingPoint - offset * 2) + gap * 3, 95, 20};
    attackSpeedLabel.p_color = BLUE;
    attackSpeedLabel.p_boundingSize = 2.0f;
    attackSpeedLabel.p_boundingColor = attackSpeedLabel.p_color * 0.8f;
    attackSpeedLabel.p_visible = false;
    attackSpeedLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();
        if (!tower)
        {
            label.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                const Tower tower = Towers::GetTowerData(placeTower);
                label.p_text = "As: " + std::format("{:.2f}", tower.p_attackSpeed);
                label.p_visible = true;
            }
        }
        else if (tower->p_isUpgradeHovered)
        {
            const Tower postUpgradeData = Towers::GetTowerData(tower->p_upgradesTo);
            label.p_text = "As: " + std::format("{:.2f}", tower->p_attackSpeed) + " -> " + std::format("{:.2f}", postUpgradeData.p_attackSpeed);
            label.p_visible = true;
        }
        else
        {
            label.p_text = "As: " + std::format("{:.2f}", tower->p_attackSpeed);
            label.p_visible = true;
        }
    };
#pragma endregion
#pragma region RangeLabel
    Label &rangeLabel = mgr_gui->AddLabel(Label{});
    rangeLabel.p_text = "R: 0";
    rangeLabel.p_id = mgr_gui->GetAmountOfLabels();
    rangeLabel.p_rect = {5, (startingPoint - offset * 1) + gap * 2, 95, 20};
    rangeLabel.p_color = BLUE;
    rangeLabel.p_boundingSize = 2.0f;
    rangeLabel.p_boundingColor = rangeLabel.p_color * 0.8f;
    rangeLabel.p_visible = false;
    rangeLabel.p_updateFunction = [this](float deltaTime, Label &label)
    {
        const Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();
        if (!tower)
        {
            label.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                const Tower tower = Towers::GetTowerData(placeTower);
                label.p_text = "R: " + std::format("{:.2f}", tower.p_range);
                label.p_visible = true;
            }
        }
        else if (tower->p_isUpgradeHovered)
        {
            const Tower postUpgradeData = Towers::GetTowerData(tower->p_upgradesTo);
            label.p_text = "R: " + std::format("{:.2f}", tower->p_range) + " -> " + std::format("{:.2f}", postUpgradeData.p_range);
            label.p_visible = true;
        }
        else
        {
            label.p_text = "R: " + std::format("{:.2f}", tower->p_range);
            label.p_visible = true;
        }
    };
#pragma endregion
}
void TowerSelect::InitButtons()
{
    constexpr size_t amountOfButtons = 1;
    mgr_gui->ReserveButton(amountOfButtons);

#pragma region UpgradeButton
    Button &upgradeButton = mgr_gui->AddButton(Button{});
    upgradeButton.p_text = "Upgrade";
    upgradeButton.p_id = mgr_gui->GetAmountOfButtons();
    upgradeButton.p_rect = {5, (startingPoint - offset * 0) + gap * 1, 95, 20};
    upgradeButton.p_color = GREEN;
    upgradeButton.p_boundingSize = 2.0f;
    upgradeButton.p_boundingColor = upgradeButton.p_color * 0.8f;
    upgradeButton.p_visible = false;
    upgradeButton.p_updateFunction = [this](float deltaTime, Button &button)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();
        button.p_color = GREEN;

        if (!tower)
        {
            button.p_visible = false;
            if (placeTower != TowerType::Nothing)
            {
                button.p_color = YELLOW;
                button.p_text = "Preview Stats";
                button.p_visible = true;
            }
        }
        else if (tower->p_upgradesTo == TowerType::Nothing)
        {
            button.p_visible = true;
            button.p_color = RED;
            button.p_boundingColor = button.p_color * 0.8f;
            button.p_text = "Max Upgrade";
        }
        else
        {
            Tower upgradedTower = Towers::GetTowerData(tower->p_upgradesTo);
            button.p_text = "Upgrade: " + std::to_string(upgradedTower.p_price) + " $";
            tower->p_isUpgradeHovered = button.p_isHovered;
            button.p_visible = true;
        }

        button.p_boundingColor = button.p_color * 0.8f;
    };
    upgradeButton.p_onPressed = [this](float deltaTime, Button &button)
    {
        Tower *tower = this->mgr_tower->GetLastSelectedTower();
        const TowerType placeTower = this->mgr_tower->GetPlaceTower();
        
        if (tower)
        {
            if (tower->p_upgradesTo == TowerType::Nothing)
            {
                return;
            }

            Basics::UpgradeTower(deltaTime, tower, mgr_ps);
        }
    };

#pragma endregion

}
void TowerSelect::InjectDependencies(TowerManager *towerManager, GuiManager *guiManager, PSManager *psManager)
{
    mgr_tower = towerManager;
    mgr_gui = guiManager;
    mgr_ps = psManager;
}
void TowerSelect::Init()
{
    assert(mgr_tower != nullptr && "TowerManager wasn't injected and its dependency");
    assert(mgr_gui != nullptr && "GuiManager wasn't injected and its dependency");
    InitLabels();
    InitButtons();
}
