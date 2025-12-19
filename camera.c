#include "camera.h"
#include <gb/gb.h>
#include "map.h"

camera_t camera = { 0 };


uint8_t get_map_tile(uint8_t grid_x, uint8_t grid_y) {
    // Check bounds
    if (grid_x >= MAP_SIDE || grid_y >= MAP_SIDE) {
        return VOID_TILE;
    }
    
    // Access the tile from the continuous array
    // Since MAP_SIDE = 32 = 2^5, we can use bit shift instead of multiply
    // index = y * 32 + x = (y << 5) + x
    return main_floor.tiles[(grid_y << 5) + grid_x];
}

static uint8_t get_background_tile(uint8_t tile_type, uint8_t quadrant) {
    // quadrant: 0=upper-left, 1=upper-right, 2=lower-left, 3=lower-right
    
    switch(tile_type) {
        case VOID_TILE:
            return BACK_VOID;
            
        case WALL_TILE:
            switch(quadrant) {
                case 0: return BACK_WALL_UL;
                case 1: return BACK_WALL_UR;
                case 2: return BACK_WALL_LL;
                case 3: return BACK_WALL_LR;
            }
            break;

        case FLOOR_TILE:
            return BACK_FLOOR;
            break;
            
        case TRAP_TILE:
            switch(quadrant) {
                case 0: return BACK_TRAP_UL;
                case 1: return BACK_TRAP_UR;
                case 2: return BACK_TRAP_LL;
                case 3: return BACK_TRAP_LR;
            }
            break;

        case EXIT_TILE:
            // TODO: handle locked exit
            switch(quadrant) {
                case 0: return BACK_EXIT_UL;
                case 1: return BACK_EXIT_UR;
                case 2: return BACK_EXIT_LL;
                case 3: return BACK_EXIT_LR;
            }
            break;
    }
    
    return BACK_VOID; // Default fallback
}

// Draw the visible portion of the map to the background
void draw_visible_map(uint8_t camera_grid_x, uint8_t camera_grid_y) {
    uint8_t screen_x, screen_y;
    uint8_t grid_x, grid_y;
    uint8_t tile_type;
    uint8_t sprite_tile;
    uint8_t quadrant;
    
    // Loop through each 8x8 tile position on screen
    for (screen_y = 0; screen_y < TILE_HEIGHT; screen_y++) {
        for (screen_x = 0; screen_x < TILE_WIDTH; screen_x++) {
            // Calculate which grid cell this screen position corresponds to
            // Each grid cell is 16x16 pixels = 2x2 tiles of 8x8
            grid_x = camera_grid_x + (screen_x >> 1);
            grid_y = camera_grid_y + (screen_y >> 1);
            
            // Get the tile type from the grid
            tile_type = get_map_tile(grid_x, grid_y);
            
            // Determine which quadrant of the 16x16 grid cell we're drawing
            // 0=UL, 1=UR, 2=LL, 3=LR
            quadrant = ((screen_y & 1) << 1) | (screen_x & 1);
            
            // Get the appropriate sprite tile
            sprite_tile = get_background_tile(tile_type, quadrant);
            
            // Set the background tile
            set_bkg_tile_xy(screen_x, screen_y, sprite_tile);
        }
    }
}


void draw_map_column(uint8_t screen_x, uint8_t camera_grid_x, uint8_t camera_grid_y) {
    uint8_t screen_y;
    uint8_t grid_x, grid_y;
    uint8_t tile_type;
    uint8_t sprite_tile;
    uint8_t quadrant;
    
    for (screen_y = 0; screen_y < TILE_HEIGHT; screen_y++) {
        grid_x = camera_grid_x + (screen_x >> 1);
        grid_y = camera_grid_y + (screen_y >> 1);
        
        tile_type = get_map_tile(grid_x, grid_y);
        quadrant = ((screen_y & 1) << 1) | (screen_x & 1);
        sprite_tile = get_background_tile(tile_type, quadrant);
        
        set_bkg_tile_xy(screen_x, screen_y, sprite_tile);
    }
}

void draw_map_row(uint8_t screen_y, uint8_t camera_grid_x, uint8_t camera_grid_y) {
    uint8_t screen_x;
    uint8_t grid_x, grid_y;
    uint8_t tile_type;
    uint8_t sprite_tile;
    uint8_t quadrant;
    
    for (screen_x = 0; screen_x < TILE_WIDTH; screen_x++) {
        grid_x = camera_grid_x + (screen_x >> 1);
        grid_y = camera_grid_y + (screen_y >> 1);
        
        tile_type = get_map_tile(grid_x, grid_y);
        quadrant = ((screen_y & 1) << 1) | (screen_x & 1);
        sprite_tile = get_background_tile(tile_type, quadrant);
        
        set_bkg_tile_xy(screen_x, screen_y, sprite_tile);
    }
}



void initial_draw(void) { 
    draw_visible_map(camera.x, camera.y); 
}

void update_map_display(void) {
    // Just redraw everything if camera moved
    if (camera.x != camera.x_prev || camera.y != camera.y_prev) {
        draw_visible_map(camera.x, camera.y);
        camera.x_prev = camera.x;
        camera.y_prev = camera.y;
    }
}
