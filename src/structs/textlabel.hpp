#pragma once
#include <cstdint>
#include <string>
#include <raylib.h>
#include <functional>

struct TextLabel
{
    Vector2 p_position = {0, 0};
    std::string p_text = "";
    Color p_color = WHITE;
    int p_fontSize = 10;
    std::function<void()> p_updateFunction = [](){};
};
