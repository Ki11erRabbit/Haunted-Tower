#ifndef CHARACTER_H
#define CHARACTER_H
#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

typedef enum character_direction {
    CHAR_UP,
    CHAR_DOWN,
    CHAR_RIGHT,
    CHAR_LEFT,
} char_dir_t;

typedef struct character_state {
    uint8_t x;
    uint8_t y;
    uint8_t direction;
    uint8_t *tiles;
    uint8_t body[4];
} char_state_t;

typedef struct player_character {
    char_state_t state;
    uint8_t color;
    uint8_t skin_tone;
    const palette_color_t *palette;
} player_t;

typedef struct monster_character {
    char_state_t state;
} monster_t;

typedef struct entity_character {
    char_state_t state;
} entity_t;

typedef struct character {
    uint8_t tag;
    union {
        monster_t monster;
        entity_t entity;
    } character;   
} char_t;

extern monster_t monsters[5];
extern entity_t entities[5];
// Represents all slots for monsters, chests, and keys
extern char_t *characters[5];
extern player_t player;



void change_char_direction(char_state_t *state, uint8_t direction); 

void change_char_position(char_state_t *state, uint8_t x, uint8_t y);

void set_char_tiles(char_state_t *state, uint8_t *tiles);

void init_player(void);


void change_skin_tone(player_t *, uint8_t);
void change_player_color(player_t *, uint8_t);
void set_player_color(player_t *);

#define NEXT_PLAYER_COLOR(player) change_player_color(&player, player.color + 1)
#define PREV_PLAYER_COLOR(player) change_player_color(&player, player.color - 1)

#define NEXT_PLAYER_SKIN_COLOR(player) change_skin_tone(&player, player.skin_tone + 1)
#define PREV_PLAYER_SKIN_COLOR(player) change_skin_tone(&player, player.skin_tone - 1)

#endif
