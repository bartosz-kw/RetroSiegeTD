#pragma once
#include <cstdint>
#include <string>
#include <raylib.h>
#include <functional>

struct TextLabel
{
    std::string p_text = "";

    std::function<void(TextLabel& label)> p_updateFunction = [](TextLabel& label){};

    Rectangle p_rect = {0, 0};
    Vector2 p_textPosition = {0,0};
    Color p_color = WHITE;

    uint16_t p_id = 0;
    uint8_t p_fontSize = 10;
    bool p_visible = true;
};
