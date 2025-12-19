#ifndef CAMERA_H
#define CAMERA_H

#include <stdint.h>

#define BACK_CLEAR 0u;
#define BACK_WALL_UL 1u;
#define BACK_WALL_UR 2u;
#define BACK_WALL_LL 3u;
#define BACK_WALL_LR 4u;
#define BACK_FLOOR_UL 5u;
#define BACK_FLOOR_UR 6u;
#define BACK_FLOOR_LL 7u;
#define BACK_FLOOR_LR 8u;
#define BACK_TRAP_UL 9u;
#define BACK_TRAP_UR 10u;
#define BACK_TRAP_LL 11u;
#define BACK_TRAP_LR 12u;
#define BACK_EXIT_UL 13u;
#define BACK_EXIT_UR 14u;
#define BACK_EXIT_LL 15u;
#define BACK_EXIT_LR 16u;
#define BACK_LOCKED_EXIT_UL 17u;
#define BACK_LOCKED_EXIT_UR 18u;
#define BACK_LOCKED_EXIT_LL 19u;
#define BACK_LOCKED_EXIT_LR 20u;
#define BACK_VOID 21u;

#define TILE_WIDTH 20u
#define TILE_HEIGHT 18u

#define OFFSET_WIDTH 10u
#define OFFSET_HEIGHT 9u

#define VISIBLE_AREA (TILE_WIDTH * TILE_HEIGHT)

extern uint8_t visible_background[VISIBLE_AREA];

typedef struct camera {
    uint8_t x;
    uint8_t y;
} camera_t;

extern camera_t camera;

#endif
