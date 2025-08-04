#pragma once
#include <cstdint>
#include <string>
#include <raylib.h>
#include <functional>

struct Button
{
    Rectangle p_rect = {0, 0, 100, 30};
    std::string p_text = "";
    Color p_color = BLUE;
    Color p_hoverColor = LIGHTGRAY;
    Color p_pressedColor = DARKBLUE;
    uint16_t p_id = 0;
    std::function<void()> p_onPressed = [](){};
    std::function<void()> p_updateFunc = [](){};
    bool p_isHovered = false;
    bool p_isPressed = false;
    bool p_visible = true;
    bool p_enabled = true;
};
