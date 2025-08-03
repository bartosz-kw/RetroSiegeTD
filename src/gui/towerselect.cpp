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
    m_textLabels.emplace_back(TextLabel{});
    TextLabel& towerInfoLabel = m_textLabels.back();
    towerInfoLabel.p_text = "Tower Info:";
    towerInfoLabel.p_id = 1;
    towerInfoLabel.p_fontSize = GetFontDefault().baseSize;
    towerInfoLabel.p_rect = {0, 250, 105, 20};
    towerInfoLabel.p_color = BLUE;
    towerInfoLabel.p_updateFunction = [&towerInfoLabel, this]()
    {
        
        Tower* tower = this->mgr_tower->GetLastSelectedTower();
        if (!tower)
        {
            towerInfoLabel.p_text = "No Tower Selected";
            return;
        }
        towerInfoLabel.p_text = std::to_string(tower->p_id);
        
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
        DrawRectangleRounded(label.p_rect, 10.0f, 4.0f, label.p_color);
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
