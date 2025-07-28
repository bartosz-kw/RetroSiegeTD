#include <cstdint>
#include <raylib.h>
enum TowerType
{
    Ninja = 1
};
struct Tower
{               
    Vector2 p_position = {0,0}         ;       
    int32_t p_id = -1;
    int16_t p_typeId = 0;
    int16_t p_tileId = 0;
    bool p_dirty = true;
};