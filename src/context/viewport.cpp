#include "viewport.hpp"

#include <raylib.h>

void Viewport::Update(const float renderScale, const Vector2 barOffset) {
    p_renderScale = renderScale;
    p_barOffset = barOffset;
}

Vector2 Viewport::ScreenToWorld(const Vector2 screen) const {
    return {(screen.x - p_barOffset.x) / p_renderScale, (screen.y - p_barOffset.y) / p_renderScale};
}

Vector2 Viewport::WorldToScreen(const Vector2 world) const {
    return {world.x * p_renderScale + p_barOffset.x, world.y * p_renderScale + p_barOffset.y};
}
