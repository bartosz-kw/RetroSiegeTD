#include <cstdint>
#include <raylib.h>
enum TowerType
{
    Ninja = 1
};
struct Tower
{               
    int64_t p_damage = 1;
    Vector2 p_position = {0,0}         ;       
    int32_t p_id = -1;
    float p_range = 30;
    float p_attackSpeed = 1;
    float p_timeToAttack = 0;
    int16_t p_typeId = 0;
    int16_t p_tileId = 0;
    bool p_dirty = true;
};