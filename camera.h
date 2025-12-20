#ifndef CAMERA_H
#define CAMERA_H

#include <stdint.h>
#include "character.h"

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


typedef struct {
    uint8_t x;           // Current grid X position (in 16x16 grid cells)
    uint8_t y;           // Current grid Y position (in 16x16 grid cells)
    uint8_t x_prev;      // Previous grid X position
    uint8_t y_prev;      // Previous grid Y position
    uint16_t pixel_x;     // Current pixel X position (0-255)
    uint16_t pixel_y;     // Current pixel Y position (0-255)
} camera_t;

extern camera_t camera;

uint8_t get_map_tile(uint8_t grid_x, uint8_t grid_y);
void draw_visible_map(uint8_t camera_grid_x, uint8_t camera_grid_y);
void draw_map_column(uint8_t screen_x, uint16_t map_pixel_x, uint16_t map_pixel_y);
void draw_map_row(uint8_t screen_y, uint16_t map_pixel_x, uint16_t map_pixel_y);
void initial_draw(void);
void scroll_camera(int8_t delta_x, int8_t delta_y);
void update_map_display(void);
// Set camera to specific pixel coordinates (0-352 for x, 0-368 for y)
void set_camera_position(uint16_t pixel_x, uint16_t pixel_y);

// Set camera to specific grid coordinates (0-31 for x and y)
// Each grid cell is 16x16 pixels
void set_camera_grid_position(uint8_t grid_x, uint8_t grid_y);

// Reset the camera state (call before initial_draw when changing levels)
void reset_camera_state(void);

void draw_sprite(char_state_t*);

#endif
