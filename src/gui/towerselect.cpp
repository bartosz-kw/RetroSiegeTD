#include "towerselect.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/towermanager.hpp"
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

void TowerSelect::InitLabels()
{
    constexpr uint8_t amountOfLabels = 5;
    m_textLabels.reserve(amountOfLabels);

    m_textLabels.emplace_back(TextLabel{});
    TextLabel& nameLabel = m_textLabels.back();
    nameLabel.p_text = "Tower Info:";
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
        nameLabel.p_text = "Tower Id: " + std::to_string(tower->p_id);
        nameLabel.p_visible = true;
        
    };

    m_textLabels.emplace_back(TextLabel{});
    TextLabel& levelLabel = m_textLabels.back();
    levelLabel.p_text = "h";
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

    m_textLabels.emplace_back(TextLabel{});
    TextLabel& damageLabel = m_textLabels.back();
    damageLabel.p_text = "D: 0";
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

    m_textLabels.emplace_back(TextLabel{});
    TextLabel& attackSpeedLabel = m_textLabels.back();
    attackSpeedLabel.p_text = "AS: 0";
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

    m_textLabels.emplace_back(TextLabel{});
    TextLabel& rangeLabel = m_textLabels.back();
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
void TowerSelect::Update()
{
    for (auto &label : m_textLabels)
    {
        UpdateTextPosition(label);
        label.p_updateFunction();
    }
}

void TowerSelect::Draw() const
{
    for (auto &label : m_textLabels)
    {
        if (!label.p_visible)
        {
            return;
        }
        constexpr float segments = 4.0f;
        constexpr float roundness = 5.0f;
        DrawRectangleRounded(label.p_rect, roundness, segments, label.p_color);
        DrawTextEx(GetFontDefault(), label.p_text.c_str(), label.p_textPosition, label.p_fontSize, 1.0f, BLACK);
    }
}

void TowerSelect::InjectDependencies(TowerManager* towerManager)
{
    mgr_tower = towerManager;
}

void TowerSelect::Init()
{
    assert(mgr_tower != nullptr && "TowerManager wasn't injected and its dependency");
    InitLabels();
}
