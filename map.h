#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define MAP_SIDE 32

#define MAPSIZE (MAP_SIDE * MAP_SIDE)
#define WALL_THRESHOLD 43U
#define FLOOR_THRESHOLD 2U

#define VOID_TILE 0U
#define WALL_TILE 1U
#define FLOOR_TILE 2U
#define TRAP_TILE 3U
#define EXIT_TILE 4U

typedef struct floor {
    uint8_t tiles[MAPSIZE];
} floor_t;

extern floor_t main_floor;


extern const palette_color_t floor_red[4];
extern const palette_color_t floor_green[4];
extern const palette_color_t floor_blue[4];
extern const palette_color_t floor_grey[4];
extern const palette_color_t floor_purple[4];

/*
 * Selects from one of the 5 floor color pallets
 */
const palette_color_t *select_floor_color(uint8_t);
void random_floor_color(void);


/*
 * This function generates a new dungeon floor.
 */
void generate_floor(void);
/*
 * This function sends the generated dungeon floor to the vram.
 */
void draw_floor(void);

#endif
