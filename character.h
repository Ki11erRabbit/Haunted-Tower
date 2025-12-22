#ifndef CHARACTER_H
#define CHARACTER_H
#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define MOVEMENT_TICKS 10
#define MOVEMENT_OFFSET 3

#define DOWN_OFFSET 0
#define UP_OFFSET 12
#define SIDE_OFFSET 24


typedef enum character_direction {
    CHAR_UP,
    CHAR_DOWN,
    CHAR_RIGHT,
    CHAR_LEFT,
} char_dir_t;

typedef enum character_movement_state {
    CHAR_MOVING,
    CHAR_STANDING,
    CHAR_TURNING,
} char_move_state_t;  

typedef struct character_state {
    uint8_t x;
    uint8_t y;
    uint16_t x_pixel;
    uint16_t y_pixel;
    uint8_t direction;
    uint8_t movement;
    uint8_t movement_ticks;
    uint8_t movement_frame;
    uint8_t *tiles;
    uint8_t body[4];
    const palette_color_t *palette;
    uint8_t tile_offset;
} char_state_t;

typedef struct player_character {
    char_state_t state;
    uint8_t color;
    uint8_t skin_tone;
} player_t;

typedef struct monster_character {
    uint8_t thing;
} monster_t;

typedef struct entity_character {
    uint8_t thing;
} entity_t;

typedef struct character {
    char_state_t state;
    uint8_t tag;
    union {
        monster_t monster;
        entity_t entity;
    } character;   
} char_t;

#define MAX_NPC 5

extern monster_t monsters[MAX_NPC];
extern entity_t entities[MAX_NPC];
// Represents all slots for monsters, chests, and keys
extern char_t *characters[MAX_NPC];
extern player_t player;


void tick_characters_for_movement(void);

void change_char_direction(char_state_t *state, uint8_t direction); 

void change_char_position(char_state_t *state, uint8_t x, uint8_t y);

void set_char_tiles(char_state_t *state, uint8_t *tiles);

void init_player(void);


void change_skin_tone(uint8_t);
void change_player_color(uint8_t);
void set_player_color();

#define NEXT_PLAYER_COLOR(player) change_player_color(player.color + 1)
#define PREV_PLAYER_COLOR(player) change_player_color(player.color - 1)

#define NEXT_PLAYER_SKIN_COLOR(player) change_skin_tone(player.skin_tone + 1)
#define PREV_PLAYER_SKIN_COLOR(player) change_skin_tone(player.skin_tone - 1)

#endif
