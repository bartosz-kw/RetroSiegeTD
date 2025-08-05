#include "guimanager.hpp"
#include "../namespaces/settings.hpp"
#include "../utility/debugUtil.hpp"
#include <raylib.h>
#include <format>
#include <algorithm>

// Private

void GuiManager::UpdateTextPosition(TextLabel &label)
{
    Vector2 textMeasurement = MeasureTextEx(GetFontDefault(),
                                            label.p_text.c_str(),
                                            label.p_fontSize, 1.0f);
    label.p_textPosition = {
        label.p_rect.x + label.p_rect.width / 2.0f - textMeasurement.x / 2.0f,
        label.p_rect.y + label.p_rect.height / 2.0f - textMeasurement.y / 2.0f};
}
void GuiManager::UpdateTextPosition(Button &button)
{
    Vector2 textMeasurement = MeasureTextEx(GetFontDefault(),
                                            button.p_text.c_str(),
                                            button.p_fontSize, 1.0f);
    button.p_textPosition = {
        button.p_rect.x + button.p_rect.width / 2.0f - textMeasurement.x / 2.0f,
        button.p_rect.y + button.p_rect.height / 2.0f - textMeasurement.y / 2.0f};
}
void GuiManager::UpdatePress(Button &button)
{
    Vector2 mousePosition = GetMousePosition();
    Rectangle scaledButtonRect =
        {
            button.p_rect.x * Settings::g_gameScale // x
            ,
            button.p_rect.y * Settings::g_gameScale // y
            ,
            button.p_rect.width * Settings::g_gameScale // width
            ,
            button.p_rect.height * Settings::g_gameScale // height
        };
    button.p_isHovered = false;
    if (!CheckCollisionPointRec(mousePosition, scaledButtonRect))
    {
        return;
    }
    button.p_isHovered = true;
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return;
    }
    button.p_onPressed(button);
}

/// Public

void GuiManager::Init()
{
}
void GuiManager::ReserveButton(size_t count)
{
    m_buttons.reserve(m_buttons.size() + count);
}
void GuiManager::ReserveLabel(size_t count)
{
    m_labels.reserve(m_labels.size() + count);
}
Button &GuiManager::AddButton(const Button &button)
{
    m_buttons.push_back(button);
    UpdateTextPosition(m_buttons.back());
    return m_buttons.back();
}
TextLabel &GuiManager::AddLabel(const TextLabel &label)
{
    m_labels.push_back(label);
    UpdateTextPosition(m_labels.back());
    return m_labels.back();
}
void GuiManager::RemoveButton(int id)
{
    m_buttons.erase(
        std::remove_if(m_buttons.begin(), m_buttons.end(),
                       [id](const Button &button)
                       { return button.p_id == id; }),
        m_buttons.end());
}
void GuiManager::RemoveLabel(int id)
{
    m_labels.erase(
        std::remove_if(m_labels.begin(), m_labels.end(),
                       [id](const TextLabel &label)
                       { return label.p_id == id; }),
        m_labels.end());
}
void GuiManager::Update()
{
    for (auto &label : m_labels)
    {
        if (label.p_updateFunction)
        {
            label.p_updateFunction(label);
        }
        UpdateTextPosition(label);
    }

    for (auto &button : m_buttons)
    {
        if (button.p_updateFunction)
        {
            button.p_updateFunction(button);
        }
        UpdateTextPosition(button);
        UpdatePress(button);
    }
}
void GuiManager::Draw() const
{
    for (const auto &label : m_labels)
    {
        if (!label.p_visible)
            continue;

        constexpr float segments = 4.0f;
        constexpr float roundness = 5.0f;
        DrawRectangleRounded(label.p_rect, roundness, segments, label.p_color);
        DrawTextEx(GetFontDefault(), label.p_text.c_str(),
                   label.p_textPosition, label.p_fontSize, 1.0f, BLACK);
    }

    for (const auto &button : m_buttons)
    {
        if (!button.p_visible)
            continue;
        Color buttonColor = button.p_color;
        if (button.p_isHovered)
        {
            buttonColor =
            {
                static_cast<unsigned char>(button.p_color.r * 0.8f),
                static_cast<unsigned char>(button.p_color.g * 0.8f),
                static_cast<unsigned char>(button.p_color.b * 0.8f),
                static_cast<unsigned char>(button.p_color.a)
            };
        }

        constexpr float segments = 4.0f;
        constexpr float roundness = 5.0f;
        DrawRectangleRounded(button.p_rect, roundness, segments, buttonColor);
        DrawTextEx(GetFontDefault(), button.p_text.c_str(),
                   button.p_textPosition, button.p_fontSize, 1.0f, BLACK);
    }
}