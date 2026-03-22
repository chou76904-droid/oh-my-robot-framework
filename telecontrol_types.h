#ifndef _TELECONTROL_TYPES_H
#define _TELECONTROL_TYPES_H

#include <stdint.h>

typedef struct telecontroldji telecontroldji;

typedef struct mouse mouse;

typedef enum
{
    TELECONTROL_PROTOCOL_NONE = 0,
    TELECONTROL_PROTOCOL_DJI_DBUS,
}telecontrol_protocol;

typedef enum {
    TELECONTROL_PARSE_OK = 0,
    TELECONTROL_PARSE_LENGTH_WRONG,
} TelecontrolParseStatus;

typedef struct mouse
{
    int16_t x;
    int16_t y;
    int16_t z;
    uint8_t left;
    uint8_t right;
}telecontrolmouse;

typedef struct telecontroldji
{
    uint16_t ch[4];
    uint8_t sw[2];
    telecontrolmouse mouse;
    uint16_t keyboard;
}telecontroldji;//解包后的数据

enum djisw
{
    swup,
    swmid,
    swdown,
};

typedef struct telecontrol_map
{
    float move_x;
    float move_y;

    float move_yam;
    float move_pit;

    uint8_t mode;
    uint8_t fire;
}telecontrol_map;

#endif
