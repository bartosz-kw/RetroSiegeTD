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
    const Vector2 textMeasurement = MeasureTextEx(Settings::g_gameFont,
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
    const Vector2 textMeasurement = MeasureTextEx(Settings::g_gameFont,
                                                  button.p_text.c_str(),
                                                  Settings::g_gameFont.baseSize, 1.0f);
    button.p_textPosition =
        {
            std::round(button.p_rect.x + button.p_rect.width / 2.0f - textMeasurement.x / 2.0f), // x
            std::round(button.p_rect.y + button.p_rect.height / 2.0f - textMeasurement.y / 2.0f) // y
        };
}
void GuiManager::UpdateImagePosition(Button &button)
{
    if (button.p_buttonImage.id == 0)
    {
        return;
    }

    button.p_imagePosition =
        {
            button.p_rect.x + button.p_rect.width / 2.0f - button.p_buttonImage.width / 2.0f // x
            ,
            button.p_rect.y + button.p_rect.height / 2.0f - button.p_buttonImage.height / 2.0f // y
        };
}
void GuiManager::UpdatePress(const float deltaTime, Button &button)
{
    const Vector2 mousePosition = GetMousePosition();
    const Rectangle scaledButtonRect =
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
    button.p_onPressed(deltaTime, button);
}
void GuiManager::UpdateLabel(const float deltaTime, TextLabel &label, const bool gameStarted)
{
    if (!(label.p_menuElement && gameStarted))
    {
        return;
    }
    if (label.p_updateFunction)
    {
        label.p_updateFunction(deltaTime, label);
    }
    UpdateTextPosition(label);
}
void GuiManager::UpdateButton(const float deltaTime, Button &button, const bool gameStarted)
{
    if (!(button.p_menuElement && gameStarted))
    {
        return;
    }
    if (button.p_updateFunction)
    {
        button.p_updateFunction(deltaTime, button);
    }
    UpdateTextPosition(button);
    UpdateImagePosition(button);
    UpdatePress(deltaTime, button);
}
void GuiManager::DrawButton(const Button &button, const bool gameStarted) const
{
    if (!button.p_visible)
    {
        return;
    }
    if (!(button.p_menuElement && gameStarted))
    {
        return;
    }

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

    Rectangle drawRect = button.p_rect;
    drawRect.x = floorf(drawRect.x);
    drawRect.y = floorf(drawRect.y);
    drawRect.width = floorf(drawRect.width);
    drawRect.height = floorf(drawRect.height);

    Vector2 drawTextPos = button.p_textPosition;
    drawTextPos.x = floorf(drawTextPos.x);
    drawTextPos.y = floorf(drawTextPos.y);

    Vector2 drawImagePos = button.p_imagePosition;
    drawImagePos.x = floorf(drawImagePos.x);
    drawImagePos.y = floorf(drawImagePos.y);

    DrawRectangleRounded(drawRect, roundness, segments, buttonColor);
    if (!button.p_text.empty())
    {
        DrawTextEx(Settings::g_gameFont, button.p_text.c_str(),
                   drawTextPos, Settings::g_gameFont.baseSize, 1.0f, BLACK);
    }
    if (button.p_buttonImage.id != 0)
    {
        DrawTextureV(button.p_buttonImage, drawImagePos, WHITE);
    }
}
void GuiManager::DrawLabel(const TextLabel &label, const bool gameStarted) const
{
    if (!label.p_visible)
    {
        return;
    }
    if (!(label.p_menuElement && gameStarted))
    {
        return;
    }

    constexpr float segments = 4.0f;
    constexpr float roundness = 5.0f;

    Rectangle drawRect = label.p_rect;
    drawRect.x = floorf(drawRect.x);
    drawRect.y = floorf(drawRect.y);
    drawRect.width = floorf(drawRect.width);
    drawRect.height = floorf(drawRect.height);

    Vector2 drawTextPos = label.p_textPosition;
    drawTextPos.x = floorf(drawTextPos.x);
    drawTextPos.y = floorf(drawTextPos.y);

    DrawRectangleRounded(drawRect, roundness, segments, label.p_color);
    DrawTextEx(Settings::g_gameFont, label.p_text.c_str(),
               drawTextPos, Settings::g_gameFont.baseSize, 1.0f, BLACK);
}

/// Public
const size_t GuiManager::GetAmountOfLabels() const
{
    return m_labels.size();
}
const size_t GuiManager::GetAmountOfButtons() const
{
    return m_buttons.size();
}
void GuiManager::ReserveButton(const size_t count)
{
    m_buttons.reserve(m_buttons.size() + count);
}
void GuiManager::ReserveLabel(const size_t count)
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
void GuiManager::RemoveButton(const int id)
{
    m_buttons.erase(
        std::remove_if(m_buttons.begin(), m_buttons.end(),
                       [id](const Button &button)
                       { return button.p_id == id; }),
        m_buttons.end());
}
void GuiManager::RemoveLabel(const int id)
{
    m_labels.erase(
        std::remove_if(m_labels.begin(), m_labels.end(),
                       [id](const TextLabel &label)
                       { return label.p_id == id; }),
        m_labels.end());
}
void GuiManager::Update(const float deltaTime, const bool gameStarted)
{
    for (auto &label : m_labels)
    {
        UpdateLabel(deltaTime, label, gameStarted);
    }

    for (auto &button : m_buttons)
    {
        UpdateButton(deltaTime, button, gameStarted);
    }
}
void GuiManager::Draw(const bool gameStarted) const
{
    for (const auto &label : m_labels)
    {
        DrawLabel(label, gameStarted);
    }

    for (const auto &button : m_buttons)
    {
        DrawButton(button, gameStarted);
    }
}
void GuiManager::Init()
{
}
