#pragma once
#include <cstdint>
#include <string>
#include <raylib.h>
#include <functional>

struct Button
{
    std::string p_text = "";

    std::function<void(float deltaTime,Button& button)> p_onPressed = [](float deltaTime,Button& button){};
    std::function<void(float deltaTime,Button& button)> p_updateFunction = [](float deltaTime,Button& button){};

    Texture p_buttonImage = { 0, 0, 0, 0, 0 };

    Rectangle p_rect = {0, 0, 100, 30};
    Vector2 p_textPosition = {0, 0};
    Vector2 p_imagePosition = {0 , 0};
    Color p_color = BLUE;

    uint16_t p_id = 0;
    bool p_isHovered = false;
    bool p_visible = true;
};
