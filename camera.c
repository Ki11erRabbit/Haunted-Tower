#include "camera.h"
#include <gb/gb.h>
#include "map.h"

uint8_t visible_background[VISIBLE_AREA];



void set_camera() {
}

void draw_tiles(uint8_t *background_pointer, uint8_t *map_pointer) {
    switch (*map_pointer) {
    case WALL_TILE:
        background_pointer[0] = BACK_WALL_UL;
        background_pointer[1] = BACK_WALL_UR;
        background_pointer[TILE_WIDTH] = BACK_WALL_LL;
        background_pointer[TILE_WIDTH + 1] = BACK_WALL_LR;
        break;
    case FLOOR_TILE:
        background_pointer[0] = BACK_FLOOR_UL;
        background_pointer[1] = BACK_FLOOR_UR;
        background_pointer[TILE_WIDTH] = BACK_FLOOR_LL;
        background_pointer[TILE_WIDTH + 1] = BACK_FLOOR_LR;
        break;
    case TRAP_TILE:
        background_pointer[0] = BACK_TRAP_UL;
        background_pointer[1] = BACK_TRAP_UR;
        background_pointer[TILE_WIDTH] = BACK_TRAP_LL;
        background_pointer[TILE_WIDTH + 1] = BACK_TRAP_LR;
        break;
    case EXIT_TILE:
        // TODO: add logic for checking if exit is locked
        background_pointer[0] = BACK_EXIT_UL;
        background_pointer[1] = BACK_EXIT_UR;
        background_pointer[TILE_WIDTH] = BACK_EXIT_LL;
        background_pointer[TILE_WIDTH + 1] = BACK_EXIT_LR;
        break;
    }        
}  

void camera_draw() {
    uint8_t *map_pointer = main_floor.tiles;
    uint8_t *map_end = main_floor.tiles + MAPSIZE;
    uint8_t *background_start = visible_background;
    uint8_t *background_pointer = visible_background;

    while (map_pointer != map_end) {
        if
    }      
    
    set_bkg_tiles(0, 0, TILE_WIDTH, TILE_HEIGHT, (uint8_t*)visible_background);
    wait_vbl_done();
}  
