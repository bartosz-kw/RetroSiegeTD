#pragma once
#include "../enums/guitype.hpp"
#include <cstdint>
#include <string>
#include <raylib.h>
#include <functional>

struct TextLabel
{
    std::string p_text = "";

    std::function<void(float deltaTime,TextLabel& label)> p_updateFunction = [](float deltaTime,TextLabel& label){};

    Rectangle p_rect = {0, 0};
    Vector2 p_textPosition = {0,0};
    Color p_color = WHITE;

    uint16_t p_id = 0;
    bool p_visible = true;
    GuiType p_elementType = GuiType::GameGui;
    
};
