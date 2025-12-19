#ifndef CAMERA_H
#define CAMERA_H

#include <stdint.h>

#define BACK_CLEAR 0u
#define BACK_WALL_UL 1u
#define BACK_WALL_UR 2u
#define BACK_WALL_LL 3u
#define BACK_WALL_LR 4u
#define BACK_FLOOR 5u
#define BACK_TRAP_UL 6u
#define BACK_TRAP_UR 7u
#define BACK_TRAP_LL 8u
#define BACK_TRAP_LR 9u
#define BACK_EXIT_UL 10u
#define BACK_EXIT_UR 11u
#define BACK_EXIT_LL 12u
#define BACK_EXIT_LR 13u
#define BACK_LOCKED_EXIT_UL 14u
#define BACK_LOCKED_EXIT_UR 15u
#define BACK_LOCKED_EXIT_LL 16u
#define BACK_LOCKED_EXIT_LR 17u
#define BACK_VOID 21u

#define TILE_WIDTH 20u
#define TILE_HEIGHT 18u

#define CAMERA_WIDTH 10u
#define CAMERA_HEIGHT 9u

#define CAMERA_HALF_WIDTH 5u
#define CAMERA_HALF_HEIGHT 4u

#define VISIBLE_AREA (TILE_WIDTH * TILE_HEIGHT)

typedef struct camera {
    uint8_t x;
    uint8_t y;
    uint8_t x_prev;
    uint8_t y_prev;
} camera_t;

extern camera_t camera;

void draw_visible_map(uint8_t camera_grid_x, uint8_t camera_grid_y);
void draw_map_column(uint8_t screen_x, uint8_t camera_grid_x, uint8_t camera_grid_y);
void draw_map_row(uint8_t screen_y, uint8_t camera_grid_x, uint8_t camera_grid_y);
void initial_draw(void);
void update_map_display(void);

#endif
