#pragma once

#include <raylib.h>

struct Viewport {
    float p_renderScale = 1.0f;
    Vector2 p_barOffset = {0.0f, 0.0f};

    void Update(float renderScale, Vector2 barOffset);

    Vector2 ScreenToWorld(Vector2 screen) const;
    Vector2 WorldToScreen(Vector2 world) const;
};
