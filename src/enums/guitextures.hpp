#pragma once
#include <cstdint>
#include "../namespaces/sprites.hpp"

enum GuiTextures : uint8_t
{
    MusicOn = 1,
    MusicOff = 2,
    RetroSiegeTD = 3,
    SpeedButton1 = 4,
    SpeedButton2 = 5,
    SpeedButton3 = 6
};

namespace GuiTextureUtility
{
    uint16_t ToTextureIndex(GuiTextures texture)
    {
        return static_cast<uint16_t>(texture) + Sprites::g_guiTextureOffset;
    }
}
