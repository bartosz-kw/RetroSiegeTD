#include "guimanager.hpp"
#include <raylib.h>
#include <format>
#include <algorithm>

void GuiManager::UpdateTextPosition(TextLabel& label)
{
    Vector2 textMeasurement = MeasureTextEx(GetFontDefault(), 
                                           label.p_text.c_str(), 
                                           label.p_fontSize, 1.0f);
    label.p_textPosition = {
        label.p_rect.x + label.p_rect.width / 2.0f - textMeasurement.x / 2.0f,
        label.p_rect.y + label.p_rect.height / 2.0f - textMeasurement.y / 2.0f
    };
}

void GuiManager::UpdateTextPosition(Button& button)
{
    Vector2 textMeasurement = MeasureTextEx(GetFontDefault(), 
                                           button.p_text.c_str(), 
                                           button.p_fontSize, 1.0f);
    button.p_textPosition = {
        button.p_rect.x + button.p_rect.width / 2.0f - textMeasurement.x / 2.0f,
        button.p_rect.y + button.p_rect.height / 2.0f - textMeasurement.y / 2.0f
    };
}

void GuiManager::Init()
{
    
}

void GuiManager::ReserveButton(size_t count)
{
    m_buttons.reserve(m_buttons.size() + count);
}

void GuiManager::ReserveLabel(size_t count)
{
    m_labels.reserve(m_buttons.size() + count);
}

void GuiManager::AddButton(const Button& button)
{
    m_buttons.push_back(button);
    UpdateTextPosition(m_buttons.back());
}

void GuiManager::AddLabel(const TextLabel& label)
{
    m_labels.push_back(label);
    UpdateTextPosition(m_labels.back());
}

void GuiManager::RemoveButton(int id)
{
    m_buttons.erase(
        std::remove_if(m_buttons.begin(), m_buttons.end(),
            [id](const Button& button) { return button.p_id == id; }),
        m_buttons.end()
    );
}

void GuiManager::RemoveLabel(int id)
{
    m_labels.erase(
        std::remove_if(m_labels.begin(), m_labels.end(),
            [id](const TextLabel& label) { return label.p_id == id; }),
        m_labels.end()
    );
}

void GuiManager::Update()
{
    for (auto& label : m_labels)
    {
        if (label.p_updateFunction)
        {
            label.p_updateFunction();
        }
        UpdateTextPosition(label);
    }

    for (auto& button : m_buttons)
    {
        if (button.p_updateFunction)
        {
            button.p_updateFunction();
        }
        UpdateTextPosition(button);

        Vector2 mousePosition = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
            CheckCollisionPointRec(mousePosition, button.p_rect))
        {
            if (button.p_onPressed)
            {
                button.p_onPressed();
            }
        }
    }
}

void GuiManager::Draw() const
{
    for (const auto& label : m_labels)
    {
        if (!label.p_visible) continue;

        constexpr float segments = 4.0f;
        constexpr float roundness = 5.0f;
        DrawRectangleRounded(label.p_rect, roundness, segments, label.p_color);
        DrawTextEx(GetFontDefault(), label.p_text.c_str(), 
                   label.p_textPosition, label.p_fontSize, 1.0f, BLACK);
    }

    for (const auto& button : m_buttons)
    {
        if (!button.p_visible) continue;

        constexpr float segments = 4.0f;
        constexpr float roundness = 5.0f;
        DrawRectangleRounded(button.p_rect, roundness, segments, button.p_color);
        DrawTextEx(GetFontDefault(), button.p_text.c_str(), 
                   button.p_textPosition, button.p_fontSize, 1.0f, BLACK);
    }
}
