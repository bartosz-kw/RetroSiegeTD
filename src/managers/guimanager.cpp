#include "guimanager.hpp"
#include "../namespaces/settings.hpp"
#include "../utility/debugUtil.hpp"
#include <raylib.h>
#include <cmath>
#include <format>
#include <algorithm>

// Private

void GuiManager::UpdateTextPosition(TextLabel &label)
{
    Vector2 textMeasurement = MeasureTextEx(Settings::g_gameFont,
                                            label.p_text.c_str(),
                                            Settings::g_gameFont.baseSize, 1.0f);
    label.p_textPosition = 
    {
        std::round(label.p_rect.x + label.p_rect.width / 2.0f - textMeasurement.x / 2.0f), // y
        std::round(label.p_rect.y + label.p_rect.height / 2.0f - textMeasurement.y / 2.0f) // x
    };
}
void GuiManager::UpdateTextPosition(Button &button)
{
    Vector2 textMeasurement = MeasureTextEx(Settings::g_gameFont,
                                            button.p_text.c_str(),
                                            Settings::g_gameFont.baseSize, 1.0f);
    button.p_textPosition = 
    {
        std::round(button.p_rect.x + button.p_rect.width / 2.0f - textMeasurement.x / 2.0f), // x
        std::round(button.p_rect.y + button.p_rect.height / 2.0f - textMeasurement.y / 2.0f) // y
    };
}
void GuiManager::UpdatePress(float deltaTime,Button &button)
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
    button.p_onPressed(deltaTime,button);
}
void GuiManager::UpdateLabel(float deltaTime,TextLabel &label)
{
    if (label.p_updateFunction)
    {
        label.p_updateFunction(deltaTime,label);
    }
    UpdateTextPosition(label);
}
void GuiManager::UpdateButton(float deltaTime,Button &button)
{
    if (button.p_updateFunction)
    {
        button.p_updateFunction(deltaTime,button);
    }
    UpdateTextPosition(button);
    UpdatePress(deltaTime,button);
}
void GuiManager::DrawButton(const Button &button) const
{
    if (!button.p_visible)
        return;
    Color buttonColor = button.p_color;
    if (button.p_isHovered)
    {
        buttonColor =
            {
                static_cast<unsigned char>(button.p_color.r * 0.8f),
                static_cast<unsigned char>(button.p_color.g * 0.8f),
                static_cast<unsigned char>(button.p_color.b * 0.8f),
                static_cast<unsigned char>(button.p_color.a)};
    }

    constexpr float segments = 4.0f;
    constexpr float roundness = 5.0f;
    DrawRectangleRounded(button.p_rect, roundness, segments, buttonColor);
    DrawTextEx(Settings::g_gameFont, button.p_text.c_str(),
               button.p_textPosition, Settings::g_gameFont.baseSize, 1.0f, BLACK);
}
void GuiManager::DrawLabel(const TextLabel &label) const
{
    if (!label.p_visible)
        return;

    constexpr float segments = 4.0f;
    constexpr float roundness = 5.0f;
    DrawRectangleRounded(label.p_rect, roundness, segments, label.p_color);
    DrawTextEx(Settings::g_gameFont, label.p_text.c_str(),
               label.p_textPosition, Settings::g_gameFont.baseSize, 1.0f, BLACK);
}

/// Public
size_t GuiManager::GetAmountOfLabels() const
{
    return m_labels.size();
}
size_t GuiManager::GetAmountOfButtons() const
{
    return m_buttons.size();
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
void GuiManager::Update(float deltaTime)
{
    for (auto &label : m_labels)
    {
        UpdateLabel(deltaTime,label);
    }

    for (auto &button : m_buttons)
    {
        UpdateButton(deltaTime,button);
    }
}
void GuiManager::Draw() const
{
    for (const auto &label : m_labels)
    {
        DrawLabel(label);
    }

    for (const auto &button : m_buttons)
    {
        DrawButton(button);
    }
}
void GuiManager::Init()
{
}

