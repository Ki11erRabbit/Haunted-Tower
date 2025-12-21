#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include "character.h"
#include "characters/Wizard.h"

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
            player.palette = player_red_white;
            break;
        case PLAYER_SKIN_BLACK:
            player.palette = player_red_black;
            break;
        case PLAYER_SKIN_TAN:
            player.palette = player_red_tan;
            break;
        }        
        break;
    case PLAYER_GREEN:
        switch (player.skin_tone) {
        case PLAYER_SKIN_WHITE:
            player.palette = player_green_white;
            break;
        case PLAYER_SKIN_BLACK:
            player.palette = player_green_black;
            break;
        case PLAYER_SKIN_TAN:
            player.palette = player_green_tan;
            break;
        }        
        break;
    case PLAYER_BLUE:
        switch (player.skin_tone) {
        case PLAYER_SKIN_WHITE:
            player.palette = player_blue_white;
            break;
        case PLAYER_SKIN_BLACK:
            player.palette = player_blue_black;
            break;
        case PLAYER_SKIN_TAN:
            player.palette = player_blue_tan;
            break;
        }        
        break;
    case PLAYER_PURPLE:
        switch (player.skin_tone) {
        case PLAYER_SKIN_WHITE:
            player.palette = player_purple_white;
            break;
        case PLAYER_SKIN_BLACK:
            player.palette = player_purple_black;
            break;
        case PLAYER_SKIN_TAN:
            player.palette = player_purple_tan;
            break;
        }        
        break;
    case PLAYER_WHITE:
        switch (player.skin_tone) {
        case PLAYER_SKIN_WHITE:
            player.palette = player_white_white;
            break;
        case PLAYER_SKIN_BLACK:
            player.palette = player_white_black;
            break;
        case PLAYER_SKIN_TAN:
            player.palette = player_white_tan;
            break;
        }        
        break;
    case PLAYER_ORANGE:
        switch (player.skin_tone) {
        case PLAYER_SKIN_WHITE:
            player.palette = player_orange_white;
            break;
        case PLAYER_SKIN_BLACK:
            player.palette = player_orange_black;
            break;
        case PLAYER_SKIN_TAN:
            player.palette = player_orange_tan;
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
            player.palette = player_red_white;
            break;
        case PLAYER_GREEN:
            player.palette = player_green_white;
            break;
        case PLAYER_BLUE:
            player.palette = player_blue_white;
            break;
        case PLAYER_PURPLE:
            player.palette = player_purple_white;
            break;
        case PLAYER_WHITE:
            player.palette = player_white_white;
            break;
        case PLAYER_ORANGE:
            player.palette = player_orange_white;
            break;
        }        
        break;
    case PLAYER_SKIN_BLACK:
        switch (player.color) {
        case PLAYER_RED:
            player.palette = player_red_black;
            break;
        case PLAYER_GREEN:
            player.palette = player_green_black;
            break;
        case PLAYER_BLUE:
            player.palette = player_blue_black;
            break;
        case PLAYER_PURPLE:
            player.palette = player_purple_black;
            break;
        case PLAYER_WHITE:
            player.palette = player_white_black;
            break;
        case PLAYER_ORANGE:
            player.palette = player_orange_black;
            break;
        }        
        break;
    case PLAYER_SKIN_TAN:
        switch (player.color) {
        case PLAYER_RED:
            player.palette = player_red_tan;
            break;
        case PLAYER_GREEN:
            player.palette = player_green_tan;
            break;
        case PLAYER_BLUE:
            player.palette = player_blue_tan;
            break;
        case PLAYER_PURPLE:
            player.palette = player_purple_tan;
            break;
        case PLAYER_WHITE:
            player.palette = player_white_tan;
            break;
        case PLAYER_ORANGE:
            player.palette = player_orange_tan;
            break;
        }        
        break;
    }
}

void set_player_color() {
    set_sprite_palette(0, 1, player.palette);
}  

monster_t monsters[5];
entity_t entities[5];
// Represents all slots for monsters, chests, and keys
char_t *characters[5];

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

void init_player(void) {
    player.state.direction = CHAR_DOWN;
    player.state.x = 4;
    player.state.y = 4;
    player.state.tiles = (uint8_t *)Wizard_tiles;
    set_sprite_data(0, 60, player.state.tiles);
    set_sprite_tile(0, 0);
    set_sprite_tile(1, 1);
    set_sprite_tile(2, 2);
    set_sprite_tile(3, 3);
    player.state.body[0] = 0;
    player.state.body[1] = 2;
    player.state.body[2] = 1;
    player.state.body[3] = 3;
    change_player_color(3);
    set_player_color();
}  
