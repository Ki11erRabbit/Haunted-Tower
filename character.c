#include "character.h"
#include "characters/Wizard.h"


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
}  
