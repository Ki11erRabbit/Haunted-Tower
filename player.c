#include <gb/gb.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>
#include <gb/hardware.h>
#include "character.h"
#include "characters/Wizard.h"
#include "camera.h"
#include "input.h"

void init_player(void) {
    player.state.direction = CHAR_DOWN;
    player.state.x = 4;
    player.state.y = 4;
    player.state.x_pixel = player.state.x * 16;
    player.state.y_pixel = player.state.y * 16;
    player.state.tiles = (uint8_t *)Wizard_tiles;
    set_sprite_data(0, Wizard_TILE_COUNT, player.state.tiles);
    player.state.tile_offset = 0;
    player.state.body[0] = 0;
    player.state.body[1] = 1;
    player.state.body[2] = 2;
    player.state.body[3] = 3;
    player.state.movement_frame = 0;
    player.state.movement = CHAR_MOVING;
    player.state.movement_ticks = MOVEMENT_TICKS;
    player.state.direction = CHAR_DOWN;
    change_player_color(3);
    set_player_color();
    update_sprite(&player.state);
    draw_sprite(&player.state);
}

void control_player(void) {
    int8_t delta_x = 0;
    int8_t delta_y = 0;

    DirectionState dir_state = get_directional_input();
    
    switch (dir_state.direction) {
    case DIR_UP:
        delta_y = -1;
        break;
    case DIR_DOWN:
        delta_y = 1;
        break;
    case DIR_LEFT:
        delta_x = -1;
        break;
    case DIR_RIGHT:
        delta_x = 1;
        break;
    case DIR_NONE:
        break;
    }
    
    move_character(&player.state, delta_x, delta_y);
    draw_sprite(&player.state);
}  
