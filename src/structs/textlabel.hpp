#pragma once
#include <cstdint>
#include <string>
#include <raylib.h>
#include <functional>

struct TextLabel
{
    Rectangle p_rect = {0, 0};
    Vector2 p_textPosition = {0,0};
    std::string p_text = "";
    Color p_color = WHITE;
    uint16_t p_id = 0;
    uint8_t p_fontSize = 10;
    std::function<void(TextLabel& label)> p_updateFunction = [](TextLabel& label){};
    bool p_visible = true;
};
