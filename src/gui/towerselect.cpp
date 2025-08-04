#include "towerselect.hpp"
#include "../utility/debugUtil.hpp"
#include "../managers/towermanager.hpp"
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
    m_textLabels.reserve(2);

    m_textLabels.emplace_back(TextLabel{});
    TextLabel& towerNameLabel = m_textLabels.back();
    towerNameLabel.p_text = "Tower Info:";
    towerNameLabel.p_id = 1;
    towerNameLabel.p_fontSize = GetFontDefault().baseSize;
    towerNameLabel.p_rect = {0, 230, 105, 20};
    towerNameLabel.p_color = BLUE;
    towerNameLabel.p_updateFunction = [&towerNameLabel, this]()
    {
        
        Tower* tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            towerNameLabel.p_visible = false;
            return;
        }
        towerNameLabel.p_text = "Tower Id: " + std::to_string(tower->p_id);
        towerNameLabel.p_visible = true;
        
    };

    m_textLabels.emplace_back(TextLabel{});
    TextLabel& towerLevelLabel = m_textLabels.back();
    towerLevelLabel.p_text = "h";
    towerLevelLabel.p_id = 1;
    towerLevelLabel.p_fontSize = GetFontDefault().baseSize;
    towerLevelLabel.p_rect = {0, 250, 21, 20};
    towerLevelLabel.p_color = BLUE;
    towerLevelLabel.p_updateFunction = [&towerLevelLabel, this]()
    {
        Tower* tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            towerLevelLabel.p_visible = false;
            return;
        }
        towerLevelLabel.p_text = "L: " + std::to_string(tower->p_level);
        towerLevelLabel.p_visible = true;
        
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
