#include <gb/gb.h>
#include "camera.h"
#include "map.h"
#include "character.h"

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


void draw_map_column(uint8_t screen_x, uint16_t map_pixel_x, uint16_t map_pixel_y) {
    uint8_t screen_y;
    uint8_t tile_type;
    uint8_t sprite_tile;
    uint8_t quadrant;
    
    // For each tile in the column (need to draw extra tiles for full coverage)
    // Drawing 19 tiles to ensure we cover the visible area plus buffer
    for (screen_y = 0; screen_y < TILE_HEIGHT + 1; screen_y++) {
        // Calculate the actual map position in pixels for this screen tile
        uint16_t actual_pixel_x = map_pixel_x;
        uint16_t actual_pixel_y = map_pixel_y + (screen_y << 3);  // screen_y * 8
        
        // Convert to grid coordinates (divide by 16)
        uint8_t grid_x = actual_pixel_x >> 4;
        uint8_t grid_y = actual_pixel_y >> 4;
        
        // Get the tile type from the grid
        tile_type = get_map_tile(grid_x, grid_y);
        
        // Determine which quadrant within the 16x16 grid cell
        // Based on the pixel position within the cell
        uint8_t sub_x = (actual_pixel_x >> 3) & 1;  // Which 8x8 tile horizontally (0 or 1)
        uint8_t sub_y = (actual_pixel_y >> 3) & 1;  // Which 8x8 tile vertically (0 or 1)
        quadrant = (sub_y << 1) | sub_x;
        
        // Get the appropriate sprite tile
        sprite_tile = get_background_tile(tile_type, quadrant);
        
        // Set the background tile at the wrapped screen position
        uint8_t wrapped_y = screen_y & 0x1F;  // Wrap at 32
        set_bkg_tile_xy(screen_x, wrapped_y, sprite_tile);
    }
}

void draw_map_row(uint8_t screen_y, uint16_t map_pixel_x, uint16_t map_pixel_y) {
    uint8_t screen_x;
    uint8_t tile_type;
    uint8_t sprite_tile;
    uint8_t quadrant;
    
    // For each tile in the row (need to draw extra tiles for full coverage)
    // Drawing 21 tiles to ensure we cover the visible area plus buffer
    for (screen_x = 0; screen_x < TILE_WIDTH + 1; screen_x++) {
        // Calculate the actual map position in pixels for this screen tile
        uint16_t actual_pixel_x = map_pixel_x + (screen_x << 3);  // screen_x * 8
        uint16_t actual_pixel_y = map_pixel_y;
        
        // Convert to grid coordinates (divide by 16)
        uint8_t grid_x = actual_pixel_x >> 4;
        uint8_t grid_y = actual_pixel_y >> 4;
        
        // Get the tile type from the grid
        tile_type = get_map_tile(grid_x, grid_y);
        
        // Determine which quadrant within the 16x16 grid cell
        uint8_t sub_x = (actual_pixel_x >> 3) & 1;
        uint8_t sub_y = (actual_pixel_y >> 3) & 1;
        quadrant = (sub_y << 1) | sub_x;
        
        // Get the appropriate sprite tile
        sprite_tile = get_background_tile(tile_type, quadrant);
        
        // Set the background tile at the wrapped screen position
        uint8_t wrapped_x = screen_x & 0x1F;  // Wrap at 32
        set_bkg_tile_xy(wrapped_x, screen_y, sprite_tile);
    }
}



void initial_draw(void) { 
    uint8_t screen_x, screen_y;
    uint8_t grid_x, grid_y;
    uint8_t tile_type;
    uint8_t sprite_tile;
    uint8_t quadrant;
    
    // Calculate the starting map pixel position
    uint16_t start_pixel_x = camera.pixel_x;
    uint16_t start_pixel_y = camera.pixel_y;
    
    // Draw enough tiles to fill the 32x32 background buffer
    // This ensures we have tiles ready when scrolling begins
    for (screen_y = 0; screen_y < 32; screen_y++) {
        for (screen_x = 0; screen_x < 32; screen_x++) {
            // Calculate actual map position in pixels
            uint16_t map_pixel_x = start_pixel_x + (screen_x << 3);
            uint16_t map_pixel_y = start_pixel_y + (screen_y << 3);
            
            // Convert to grid coordinates (divide by 16)
            grid_x = map_pixel_x >> 4;
            grid_y = map_pixel_y >> 4;
            
            // Get the tile type from the grid
            tile_type = get_map_tile(grid_x, grid_y);
            
            // Determine which quadrant within the 16x16 grid cell
            uint8_t sub_x = (map_pixel_x >> 3) & 1;
            uint8_t sub_y = (map_pixel_y >> 3) & 1;
            quadrant = (sub_y << 1) | sub_x;
            
            // Get the appropriate sprite tile
            sprite_tile = get_background_tile(tile_type, quadrant);
            
            // Set the background tile
            set_bkg_tile_xy(screen_x, screen_y, sprite_tile);
        }
    }
    
    // Set initial scroll position
    SCX_REG = camera.pixel_x;
    SCY_REG = camera.pixel_y;
}

// Scroll the camera by a given number of pixels in each direction
// Positive values scroll right/down, negative values scroll left/up
// Automatically clamps to map boundaries
void scroll_camera(int8_t delta_x, int8_t delta_y) {
    int16_t new_x, new_y;
    
    // Calculate max scroll positions
    // Map is 32 nodes * 16 pixels = 512 pixels total
    const uint16_t MAX_SCROLL_X = (32 * 16) - 160;  // 352
    const uint16_t MAX_SCROLL_Y = (32 * 16) - 144;  // 368
    
    // Handle horizontal scrolling
    if (delta_x != 0) {
        new_x = (int16_t)camera.pixel_x + delta_x;
        
        if (new_x < 0) {
            camera.pixel_x = 0;
        } else if (new_x > MAX_SCROLL_X) {
            camera.pixel_x = MAX_SCROLL_X;
        } else {
            camera.pixel_x = (uint16_t)new_x;
        }
    }
    
    // Handle vertical scrolling
    if (delta_y != 0) {
        new_y = (int16_t)camera.pixel_y + delta_y;
        
        if (new_y < 0) {
            camera.pixel_y = 0;
        } else if (new_y > MAX_SCROLL_Y) {
            camera.pixel_y = MAX_SCROLL_Y;
        } else {
            camera.pixel_y = (uint16_t)new_y;
        }
    }
}


static uint8_t first_call = 1;

void reset_camera_state(void) {
    first_call = 0;
}  


// Set camera to specific pixel coordinates
// This will clamp to valid map boundaries and redraw the visible area
void set_camera_position(uint16_t pixel_x, uint16_t pixel_y) {
    // Calculate max scroll positions
    const uint16_t MAX_SCROLL_X = (32 * 16) - 160;  // 352
    const uint16_t MAX_SCROLL_Y = (32 * 16) - 144;  // 368
    
    // Clamp to valid range
    if (pixel_x > MAX_SCROLL_X) {
        pixel_x = MAX_SCROLL_X;
    }
    if (pixel_y > MAX_SCROLL_Y) {
        pixel_y = MAX_SCROLL_Y;
    }
    
    // Update camera position
    camera.pixel_x = pixel_x;
    camera.pixel_y = pixel_y;
    camera.x = pixel_x >> 4;  // Convert to grid coordinates
    camera.y = pixel_y >> 4;
    
    // Reset the scrolling system and redraw
    reset_camera_state();
    initial_draw();
}

// Set camera to specific grid coordinates (each grid cell is 16x16 pixels)
void set_camera_grid_position(uint8_t grid_x, uint8_t grid_y) {
    // Convert grid coordinates to pixel coordinates
    uint16_t pixel_x = (uint16_t)grid_x << 4;  // grid_x * 16
    uint16_t pixel_y = (uint16_t)grid_y << 4;  // grid_y * 16
    
    set_camera_position(pixel_x, pixel_y);
}

void update_map_display(void) {
    static uint16_t last_scroll_x = 0;
    static uint16_t last_scroll_y = 0;
    
    uint16_t scroll_x = camera.pixel_x;
    uint16_t scroll_y = camera.pixel_y;
    
    // On first call, initialize last_scroll values to current position
    if (first_call) {
        last_scroll_x = scroll_x;
        last_scroll_y = scroll_y;
        first_call = 0;
        return;  // Don't process any scrolling on first call
    }
    
    // Calculate which 8x8 tile positions we're at
    uint16_t tile_x = scroll_x >> 3;
    uint16_t tile_y = scroll_y >> 3;
    uint16_t last_tile_x = last_scroll_x >> 3;
    uint16_t last_tile_y = last_scroll_y >> 3;
    
    // Handle horizontal scrolling
    if (tile_x != last_tile_x) {
        if (scroll_x > last_scroll_x) {
            // Scrolling right - need to draw columns
            uint16_t cols_to_draw = tile_x - last_tile_x;
            for (uint16_t i = 0; i < cols_to_draw; i++) {
                uint16_t draw_tile_x = last_tile_x + 1 + i;
                uint16_t map_pixel_x = (draw_tile_x << 3) + 160;  // 20 tiles ahead
                uint8_t screen_col = (uint8_t)((draw_tile_x + 20) & 0x1F);
                
                // Draw the entire column at this position
                for (uint8_t row = 0; row < 19; row++) {
                    uint16_t map_pixel_y = scroll_y + (row << 3);
                    uint8_t screen_row = (uint8_t)((scroll_y >> 3) + row) & 0x1F;
                    
                    uint8_t grid_x = map_pixel_x >> 4;
                    uint8_t grid_y = map_pixel_y >> 4;
                    uint8_t tile_type = get_map_tile(grid_x, grid_y);
                    
                    uint8_t sub_x = (map_pixel_x >> 3) & 1;
                    uint8_t sub_y = (map_pixel_y >> 3) & 1;
                    uint8_t quadrant = (sub_y << 1) | sub_x;
                    uint8_t sprite_tile = get_background_tile(tile_type, quadrant);
                    
                    set_bkg_tile_xy(screen_col, screen_row, sprite_tile);
                }
            }
        } else {
            // Scrolling left - need to draw columns
            uint16_t cols_to_draw = last_tile_x - tile_x;
            for (uint16_t i = 0; i < cols_to_draw; i++) {
                uint16_t draw_tile_x = tile_x + i;
                uint16_t map_pixel_x = draw_tile_x << 3;
                uint8_t screen_col = (uint8_t)(draw_tile_x & 0x1F);
                
                // Draw the entire column at this position
                for (uint8_t row = 0; row < 19; row++) {
                    uint16_t map_pixel_y = scroll_y + (row << 3);
                    uint8_t screen_row = (uint8_t)((scroll_y >> 3) + row) & 0x1F;
                    
                    uint8_t grid_x = map_pixel_x >> 4;
                    uint8_t grid_y = map_pixel_y >> 4;
                    uint8_t tile_type = get_map_tile(grid_x, grid_y);
                    
                    uint8_t sub_x = (map_pixel_x >> 3) & 1;
                    uint8_t sub_y = (map_pixel_y >> 3) & 1;
                    uint8_t quadrant = (sub_y << 1) | sub_x;
                    uint8_t sprite_tile = get_background_tile(tile_type, quadrant);
                    
                    set_bkg_tile_xy(screen_col, screen_row, sprite_tile);
                }
            }
        }
        last_scroll_x = scroll_x;
    }
    
    // Handle vertical scrolling
    if (tile_y != last_tile_y) {
        if (scroll_y > last_scroll_y) {
            // Scrolling down - need to draw rows
            uint16_t rows_to_draw = tile_y - last_tile_y;
            for (uint16_t i = 0; i < rows_to_draw; i++) {
                uint16_t draw_tile_y = last_tile_y + 1 + i;
                uint16_t map_pixel_y = (draw_tile_y << 3) + 144;  // 18 tiles ahead
                uint8_t screen_row = (uint8_t)((draw_tile_y + 18) & 0x1F);
                
                // Draw the entire row at this position
                for (uint8_t col = 0; col < 21; col++) {
                    uint16_t map_pixel_x = scroll_x + (col << 3);
                    uint8_t screen_col = (uint8_t)((scroll_x >> 3) + col) & 0x1F;
                    
                    uint8_t grid_x = map_pixel_x >> 4;
                    uint8_t grid_y = map_pixel_y >> 4;
                    uint8_t tile_type = get_map_tile(grid_x, grid_y);
                    
                    uint8_t sub_x = (map_pixel_x >> 3) & 1;
                    uint8_t sub_y = (map_pixel_y >> 3) & 1;
                    uint8_t quadrant = (sub_y << 1) | sub_x;
                    uint8_t sprite_tile = get_background_tile(tile_type, quadrant);
                    
                    set_bkg_tile_xy(screen_col, screen_row, sprite_tile);
                }
            }
        } else {
            // Scrolling up - need to draw rows
            uint16_t rows_to_draw = last_tile_y - tile_y;
            for (uint16_t i = 0; i < rows_to_draw; i++) {
                uint16_t draw_tile_y = tile_y + i;
                uint16_t map_pixel_y = draw_tile_y << 3;
                uint8_t screen_row = (uint8_t)(draw_tile_y & 0x1F);
                
                // Draw the entire row at this position
                for (uint8_t col = 0; col < 21; col++) {
                    uint16_t map_pixel_x = scroll_x + (col << 3);
                    uint8_t screen_col = (uint8_t)((scroll_x >> 3) + col) & 0x1F;
                    
                    uint8_t grid_x = map_pixel_x >> 4;
                    uint8_t grid_y = map_pixel_y >> 4;
                    uint8_t tile_type = get_map_tile(grid_x, grid_y);
                    
                    uint8_t sub_x = (map_pixel_x >> 3) & 1;
                    uint8_t sub_y = (map_pixel_y >> 3) & 1;
                    uint8_t quadrant = (sub_y << 1) | sub_x;
                    uint8_t sprite_tile = get_background_tile(tile_type, quadrant);
                    
                    set_bkg_tile_xy(screen_col, screen_row, sprite_tile);
                }
            }
        }
        last_scroll_y = scroll_y;
    }
    
    // Update grid tracking
    camera.x = scroll_x >> 4;
    camera.y = scroll_y >> 4;
    
    // Update hardware scroll registers for smooth scrolling
    SCX_REG = (uint8_t)(scroll_x & 0xFF);
    SCY_REG = (uint8_t)(scroll_y & 0xFF);
}


void draw_sprite(char_state_t *character) {
    if (!(character->x >= camera.x && character->x <= (camera.x + TILE_WIDTH))) {
        move_sprite(character->body[0], 0, 0);
        move_sprite(character->body[1], 0, 0);
        move_sprite(character->body[2], 0, 0);
        move_sprite(character->body[3], 0, 0);
        return;
    }    
    if (!(character->y >= camera.y && character->y <= (camera.y + TILE_HEIGHT))) {
        move_sprite(character->body[0], 0, 0);
        move_sprite(character->body[1], 0, 0);
        move_sprite(character->body[2], 0, 0);
        move_sprite(character->body[3], 0, 0);
        return;
    }

    uint16_t pixel_x = character->x_pixel;
    uint16_t pixel_y = character->y_pixel;

    move_sprite(character->body[0], pixel_x, pixel_y);
    move_sprite(character->body[1], pixel_x + 8, pixel_y);
    move_sprite(character->body[2], pixel_x, pixel_y + 8);
    move_sprite(character->body[3], pixel_x + 8, pixel_y + 8);
}


void update_sprite(char_state_t *character) {
    
    uint8_t tl, tr, bl, br;

    if (character->movement == CHAR_MOVING) {
        uint8_t offset;
        switch (character->direction) {
        case CHAR_DOWN:
            offset = DOWN_OFFSET;
            break;
        case CHAR_UP:
            offset = UP_OFFSET;
            break;
        case CHAR_LEFT:
            offset = SIDE_OFFSET;
            break;
        case CHAR_RIGHT:
            offset = SIDE_OFFSET;
            break;
        }
        uint8_t frame;
        if (character->movement_frame == 3) {
            // This handles the case where we are on the last frame
            frame = 1;
        } else {
            frame = character->movement_frame;
        }
        if (character->direction == CHAR_RIGHT) {
            tr = character->tile_offset + offset + frame * 4;
            tl = character->tile_offset + offset + frame * 4 + 1;
            br = character->tile_offset + offset + frame * 4 + 2;
            bl = character->tile_offset + offset + frame * 4 + 3;
        } else {
            tl = character->tile_offset + offset + frame * 4;
            tr = character->tile_offset + offset + frame * 4 + 1;
            bl = character->tile_offset + offset + frame * 4 + 2;
            br = character->tile_offset + offset + frame * 4 + 3;
        }
    } else if (character->movement == CHAR_TURNING) {
        if ((character->direction == CHAR_RIGHT && character->movement_frame == 1) || (character->last_direction == CHAR_RIGHT && character->movement_frame == 0)) {
            tr = character->tile_offset + character->turn_frame_offset[character->movement_frame] * 4;
            tl = character->tile_offset + character->turn_frame_offset[character->movement_frame] * 4 + 1;
            br = character->tile_offset + character->turn_frame_offset[character->movement_frame] * 4 + 2;
            bl = character->tile_offset + character->turn_frame_offset[character->movement_frame] * 4 + 3;
        } else {
            tl = character->tile_offset + character->turn_frame_offset[character->movement_frame] * 4;
            tr = character->tile_offset + character->turn_frame_offset[character->movement_frame] * 4 + 1;
            bl = character->tile_offset + character->turn_frame_offset[character->movement_frame] * 4 + 2;
            br = character->tile_offset + character->turn_frame_offset[character->movement_frame] * 4 + 3;
        }
    }                                          
    
    set_sprite_tile(character->body[0], tl);
    set_sprite_tile(character->body[1], tr);
    set_sprite_tile(character->body[2], bl);
    set_sprite_tile(character->body[3], br);

    if ((character->direction == CHAR_RIGHT &&
         character->movement == CHAR_MOVING) ||
        (character->movement == CHAR_TURNING &&
         character->direction == CHAR_RIGHT &&
         character->movement_frame == 1) ||
        (character->movement == CHAR_TURNING &&
         character->last_direction == CHAR_RIGHT &&
         character->movement_frame == 2)) {
        set_sprite_prop(character->body[0], S_FLIPX);
        set_sprite_prop(character->body[1], S_FLIPX);
        set_sprite_prop(character->body[2], S_FLIPX);
        set_sprite_prop(character->body[3], S_FLIPX);
    } else {
        set_sprite_prop(character->body[0], 0);
        set_sprite_prop(character->body[1], 0);
        set_sprite_prop(character->body[2], 0);
        set_sprite_prop(character->body[3], 0);
    }      
}
