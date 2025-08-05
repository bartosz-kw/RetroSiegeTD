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
    Vector2 p_textPosition = {0,0};
    uint16_t p_id = 0;
    float p_fontSize = 10.0f;
    std::function<void(Button& button)> p_onPressed = [](Button& button){};
    std::function<void(Button& button)> p_updateFunction = [](Button& button){};
    bool p_isHovered = false;
    bool p_visible = true;
};
