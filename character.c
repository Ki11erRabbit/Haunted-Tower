#include <gb/gb.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include "character.h"
#include "characters/Wizard.h"
#include "camera.h"

enum player_color {
    PLAYER_RED,
    PLAYER_GREEN,
    PLAYER_BLUE,
    PLAYER_PURPLE,
    PLAYER_WHITE,
    PLAYER_ORANGE
};

enum player_skin_color {
  PLAYER_SKIN_WHITE,
  PLAYER_SKIN_BLACK,
  PLAYER_SKIN_TAN,
};  

// White Skin Red
const palette_color_t player_red_white[4] = {
    0,
    RGB8(249, 210, 161),
    RGB8(242, 50, 56),
    RGB(0, 0, 0),
};
// Black Skin Red
const palette_color_t player_red_black[4] = {
    0,
    RGB8(155, 98, 44),
    RGB8(242, 50, 56),
    RGB(0, 0, 0),
};
/// Tan Skin Red
const palette_color_t player_red_tan[4] = {
    0,
    RGB8(221, 177, 136),
    RGB8(242, 50, 56),
    RGB(0, 0, 0),
};

// White Skin Green
const palette_color_t player_green_white[4] = {
    0,
    RGB8(249, 210, 161),
    RGB8(60, 215, 69),
    RGB(0, 0, 0),
};
// Black Skin Green
const palette_color_t player_green_black[4] = {
    0,
    RGB8(155, 98, 44),
    RGB8(60, 215, 69),
    RGB(0, 0, 0),
};
/// Tan Skin Green
const palette_color_t player_green_tan[4] = {
    0,
    RGB8(221, 177, 136),
    RGB8(60, 215, 69),
    RGB(0, 0, 0),
};

// White Skin Blue
const palette_color_t player_blue_white[4] = {
    0,
    RGB8(249, 210, 161),
    RGB8(54, 56, 212),
    RGB(0, 0, 0),
};
// Black Skin Blue
const palette_color_t player_blue_black[4] = {
    0,
    RGB8(155, 98, 44),
    RGB8(54, 56, 212),
    RGB(0, 0, 0),
};
/// Tan Skin Blue
const palette_color_t player_blue_tan[4] = {
    0,
    RGB8(221, 177, 136),
    RGB8(54, 56, 212),
    RGB(0, 0, 0),
};

// White Skin Purple
const palette_color_t player_purple_white[4] = {
    0,
    RGB8(249, 210, 161),
    RGB8(134, 81, 203),
    RGB(0, 0, 0),
};
// Black Skin Purple
const palette_color_t player_purple_black[4] = {
    0,
    RGB8(155, 98, 44),
    RGB8(134, 81, 203),
    RGB(0, 0, 0),
};
/// Tan Skin Purple
const palette_color_t player_purple_tan[4] = {
    0,
    RGB8(221, 177, 136),
    RGB8(134, 81, 203),
    RGB(0, 0, 0),
};

// White Skin White
const palette_color_t player_white_white[4] = {
    0,
    RGB8(249, 210, 161),
    RGB8(239, 236, 244),
    RGB(0, 0, 0),
};
// Black Skin White
const palette_color_t player_white_black[4] = {
    0,
    RGB8(155, 98, 44),
    RGB8(239, 236, 244),
    RGB(0, 0, 0),
};
/// Tan Skin White
const palette_color_t player_white_tan[4] = {
    0,
    RGB8(221, 177, 136),
    RGB8(239, 236, 244),
    RGB(0, 0, 0),
};

// White Skin Orange
const palette_color_t player_orange_white[4] = {
    0,
    RGB8(249, 210, 161),
    RGB8(243, 158, 40),
    RGB(0, 0, 0),
};
// Black Skin Orange
const palette_color_t player_orange_black[4] = {
    0,
    RGB8(155, 98, 44),
    RGB8(243, 158, 40),
    RGB(0, 0, 0),
};
/// Tan Skin Orange
const palette_color_t player_orange_tan[4] = {
    0,
    RGB8(221, 177, 136),
    RGB8(243, 158, 40),
    RGB(0, 0, 0),
};

void change_skin_tone(uint8_t value) {
    value = value % 3;
    player.skin_tone = value;
    switch (player.color) {
    case PLAYER_RED:
        switch (player.skin_tone) {
        case PLAYER_SKIN_WHITE:
            player.state.palette = player_red_white;
            break;
        case PLAYER_SKIN_BLACK:
            player.state.palette = player_red_black;
            break;
        case PLAYER_SKIN_TAN:
            player.state.palette = player_red_tan;
            break;
        }        
        break;
    case PLAYER_GREEN:
        switch (player.skin_tone) {
        case PLAYER_SKIN_WHITE:
            player.state.palette = player_green_white;
            break;
        case PLAYER_SKIN_BLACK:
            player.state.palette = player_green_black;
            break;
        case PLAYER_SKIN_TAN:
            player.state.palette = player_green_tan;
            break;
        }        
        break;
    case PLAYER_BLUE:
        switch (player.skin_tone) {
        case PLAYER_SKIN_WHITE:
            player.state.palette = player_blue_white;
            break;
        case PLAYER_SKIN_BLACK:
            player.state.palette = player_blue_black;
            break;
        case PLAYER_SKIN_TAN:
            player.state.palette = player_blue_tan;
            break;
        }        
        break;
    case PLAYER_PURPLE:
        switch (player.skin_tone) {
        case PLAYER_SKIN_WHITE:
            player.state.palette = player_purple_white;
            break;
        case PLAYER_SKIN_BLACK:
            player.state.palette = player_purple_black;
            break;
        case PLAYER_SKIN_TAN:
            player.state.palette = player_purple_tan;
            break;
        }        
        break;
    case PLAYER_WHITE:
        switch (player.skin_tone) {
        case PLAYER_SKIN_WHITE:
            player.state.palette = player_white_white;
            break;
        case PLAYER_SKIN_BLACK:
            player.state.palette = player_white_black;
            break;
        case PLAYER_SKIN_TAN:
            player.state.palette = player_white_tan;
            break;
        }        
        break;
    case PLAYER_ORANGE:
        switch (player.skin_tone) {
        case PLAYER_SKIN_WHITE:
            player.state.palette = player_orange_white;
            break;
        case PLAYER_SKIN_BLACK:
            player.state.palette = player_orange_black;
            break;
        case PLAYER_SKIN_TAN:
            player.state.palette = player_orange_tan;
            break;
        }        
        break;
    }    
}

void change_player_color(uint8_t value) {
    value = value % 6;
    player.color = value;
    switch (player.skin_tone) {
    case PLAYER_SKIN_WHITE:
        switch (player.color) {
        case PLAYER_RED:
            player.state.palette = player_red_white;
            break;
        case PLAYER_GREEN:
            player.state.palette = player_green_white;
            break;
        case PLAYER_BLUE:
            player.state.palette = player_blue_white;
            break;
        case PLAYER_PURPLE:
            player.state.palette = player_purple_white;
            break;
        case PLAYER_WHITE:
            player.state.palette = player_white_white;
            break;
        case PLAYER_ORANGE:
            player.state.palette = player_orange_white;
            break;
        }        
        break;
    case PLAYER_SKIN_BLACK:
        switch (player.color) {
        case PLAYER_RED:
            player.state.palette = player_red_black;
            break;
        case PLAYER_GREEN:
            player.state.palette = player_green_black;
            break;
        case PLAYER_BLUE:
            player.state.palette = player_blue_black;
            break;
        case PLAYER_PURPLE:
            player.state.palette = player_purple_black;
            break;
        case PLAYER_WHITE:
            player.state.palette = player_white_black;
            break;
        case PLAYER_ORANGE:
            player.state.palette = player_orange_black;
            break;
        }        
        break;
    case PLAYER_SKIN_TAN:
        switch (player.color) {
        case PLAYER_RED:
            player.state.palette = player_red_tan;
            break;
        case PLAYER_GREEN:
            player.state.palette = player_green_tan;
            break;
        case PLAYER_BLUE:
            player.state.palette = player_blue_tan;
            break;
        case PLAYER_PURPLE:
            player.state.palette = player_purple_tan;
            break;
        case PLAYER_WHITE:
            player.state.palette = player_white_tan;
            break;
        case PLAYER_ORANGE:
            player.state.palette = player_orange_tan;
            break;
        }        
        break;
    }
}

void set_player_color() {
    set_sprite_palette(0, 1, player.state.palette);
}  

monster_t monsters[5];
entity_t entities[5];
// Represents all slots for monsters, chests, and keys
char_t *characters[5] = {0, 0, 0, 0, 0};

player_t player;


void change_char_direction(char_state_t *state, uint8_t direction) {
    state->direction = direction;
}

void change_char_position(char_state_t *state, uint8_t x, uint8_t y) {
    state->x = x;
    state->y = y;
}

void set_char_tiles(char_state_t *state, uint8_t *tiles) {
    state->tiles = tiles;
}

void move_character(char_state_t *state, int8_t dx, int8_t dy) {
    if (state->movement == CHAR_MOVING) {
        uint16_t pixel_x = (uint16_t)state->x * 16;
        uint16_t pixel_y = (uint16_t)state->y * 16;
        if (state->x_pixel == pixel_x && state->y_pixel == pixel_y) {
            state->movement = CHAR_STANDING;
        } else {
            int16_t delta_x = (int16_t)pixel_x - (int16_t)state->x_pixel;
            int16_t delta_y = (int16_t)pixel_y - (int16_t)state->y_pixel;
            if (delta_x < 0) {
                state->x_pixel -= 1;
            } else if (delta_x > 0) {
                state->x_pixel += 1;
            }              
            if (delta_y < 0) {
                state->y_pixel -= 1;
            } else if (delta_y > 0) {
                state->y_pixel += 1;
            }
        }          
        return;
    }
    uint8_t new_x = state->x;
    uint8_t new_y = state->y;
    if (dx < 0) {
        new_x -= 1;
    } else if (dx > 0) {
        new_x += 1;
    }      
    if (dy < 0) {
        new_y -= 1;
    } else if (dy > 0) {
        new_y += 1;
    }
    state->x = new_x;
    state->y = new_y;
    state->movement = CHAR_MOVING;
}

void turn_character(char_state_t *state, uint8_t direction) {
    if (state->movement == CHAR_TURNING && state->movement_frame == 2) {
      state->movement = CHAR_STANDING;
      return;
    }
    state->last_direction = state->direction;
    state->direction = direction;
    switch (state->last_direction) {
    case CHAR_DOWN:
        state->turn_frame_offset[0] = state->tile_offset + DOWN_OFFSET;
        break;
    case CHAR_UP:
        state->turn_frame_offset[0] = state->tile_offset + UP_OFFSET;
        break;
    case CHAR_RIGHT:
    case CHAR_LEFT:
        state->turn_frame_offset[0] = state->tile_offset + SIDE_OFFSET;
        break;
    }      
    switch (state->direction) {
    case CHAR_DOWN:
        state->turn_frame_offset[1] = state->tile_offset + DOWN_OFFSET;
        break;
    case CHAR_UP:
        state->turn_frame_offset[1] = state->tile_offset + UP_OFFSET;
        break;
    case CHAR_RIGHT:
    case CHAR_LEFT:
        state->turn_frame_offset[1] = state->tile_offset + SIDE_OFFSET;
        break;
    }      
}  

void tick_character_for_movement(char_state_t *state) {
    switch (state->movement) {
    case CHAR_STANDING:
        // If we are standing, simply reset movement ticks
        state->movement_ticks = MOVEMENT_TICKS;
        break;
    case CHAR_MOVING:
        // If we are moving, reduce ticks by one
        --state->movement_ticks;
        if (state->movement_ticks == 0) {
            // If ticks is 0, then update the frame of the character
            state->movement_frame = (state->movement_frame + 1) % MOVEMENT_FRAMES;
            
            state->movement_ticks = MOVEMENT_TICKS;
            update_sprite(state);
            draw_sprite(state);
        }          
        break;
    case CHAR_TURNING:
        --state->movement_ticks;
        if (state->movement_ticks == 0) {
            // If ticks is 0, then update the frame of the character
            state->movement_frame = (state->movement_frame + 1) % 3;
            
            state->movement_ticks = MOVEMENT_TICKS;
            update_sprite(state);
            draw_sprite(state);
        }          
        break;
    }      
}  

void tick_characters_for_movement(void) {
    tick_character_for_movement(&player.state);
    for (char_t *character = (char_t *)characters; character < ((char_t*)characters) + MAX_NPC;
         character++) {
        if (character == 0) {
            continue;
        }        
        tick_character_for_movement(&character->state);
    }      
}


