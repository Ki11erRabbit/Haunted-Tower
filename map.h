#ifndef MAP_H
#define MAP_H

#include <stdint.h>


#define MAPSIZE (32 * 32)
#define WALL_THRESHOLD 43U
#define FLOOR_THRESHOLD 2U

#define WALL_TILE 1U
#define FLOOR_TILE 2U
#define TRAP_TILE 3U
#define EXIT_TILE 4U

typedef enum player_direction {
  PLAYER_UP,
  PLAYER_DOWN,
  PLAYER_RIGHT,
  PLAYER_LEFT,
} player_dir_t;


typedef struct floor {
    int8_t tiles[MAPSIZE];
} floor_t;

extern floor_t main_floor;

/*
 * This function generates a new dungeon floor.
 */
void generate_floor(void);
/*
 * This function sends the generated dungeon floor to the vram.
 */
void draw_floor(void);

#endif
