#pragma once
#include <string>
#include <raylib.h>
#include <cstdint>

enum ParticleMoveType : uint8_t
{
    Up = 1,
    UpWiggle = 2
};

struct Particle
{
    std::string p_text = "";
    Rectangle p_sourceRect = {0, 0, 0, 0};
    Color p_color = WHITE;
    Vector2 p_position = {0, 0};
    ParticleMoveType p_particleMoveType = ParticleMoveType::Up;
    float p_rotation = 0.0f;
    float p_aliveTime = 0.0f;
};
