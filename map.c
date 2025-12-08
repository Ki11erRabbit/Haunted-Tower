#include <gb/gb.h>
#include <gb/hardware.h>
#include <stdint.h>
#include "map.h"
#include "noise.h"
#include "map.h"
#include <rand.h>

#define MAXSMALL_ROOMS 16


floor_t main_floor;



void initialize_floor(floor_t *floor) {
  uint8_t value = rand();
  const uint8_t *noise_map1 = get_perlin_noise(value);
  value = rand();
  const uint8_t *noise_map2 = get_perlin_noise(value);
  const uint8_t threshold = WALL_THRESHOLD + (rand() % 20);
  const uint8_t *noise1_end = noise_map1 + NOISE_SIZE;
  const uint8_t *noise2_end = noise_map2 + NOISE_SIZE;
  uint8_t *tiles = (uint8_t*)floor->tiles;
  uint8_t col = 0;
  uint8_t row = 0;
  for (; noise_map1 < noise1_end; noise_map1++, noise_map2++, tiles++) {
    if (row == 0 || row == 31) {
      *tiles = WALL_TILE;
    } else if (col == 0 || col == 31) {
      *tiles = WALL_TILE;
    } else {
      if ((*noise_map1 + *noise_map2) >= WALL_THRESHOLD) {
        *tiles = WALL_TILE;
      } else {
        *tiles = FLOOR_TILE;
      }
    }
    col++;
    if (col == 32) {
      col = 0;
      row++;
    }      
  }
}

void put_in_more_walls(floor_t *floor) {
  uint8_t value = rand();
  const uint8_t *noise_map = get_voronoi_noise(value);
  const uint8_t threshold = WALL_THRESHOLD - (rand() % 20);
  const uint8_t *noise_end = noise_map + NOISE_SIZE;
  uint8_t *tiles = (uint8_t*)floor->tiles;
  uint8_t col = 0;
  uint8_t row = 0;
  for (; noise_map < noise_end; noise_map++, tiles++) {
    if (row == 0 || row == 31) {
      goto end;
    } else if (col == 0 || col == 31) {
      goto end;
    } else {
      if (*noise_map >= threshold) {
        *tiles = WALL_TILE;
      }
    }
  end:
    col++;
    if (col == 32) {
      col = 0;
      row++;
    }      
  }
}  

void add_more_floor(floor_t *floor) {
  uint8_t value = rand();
  const uint8_t *noise_map1 = get_perlin_noise(value);
  value = rand();
  const uint8_t *noise_map2 = get_perlin_noise(value);
  const uint8_t threshold = WALL_THRESHOLD + (rand() % 20);
  const uint8_t *noise1_end = noise_map1 + NOISE_SIZE;
  const uint8_t *noise2_end = noise_map2 + NOISE_SIZE;
  uint8_t *tiles = (uint8_t*)floor->tiles;
  uint8_t col = 0;
  uint8_t row = 0;
  for (; noise_map1 < noise1_end; noise_map1++, noise_map2++, tiles++) {
    if (row == 0 || row == 31) {
      goto end;
    } else if (col == 0 || col == 31) {
      goto end;
    } else {
      if ((*noise_map1 + *noise_map2) >= threshold) {
        *tiles = FLOOR_TILE;
      }
    }
  end:
    col++;
    if (col == 32) {
      col = 0;
      row++;
    }      
  }
}

typedef enum direction {
  DIRECTION_UP = 1,
  DIRECTION_DOWN,
  DIRECTION_LEFT,
  DIRECTION_RIGHT
} direction_t;

direction_t select_direction(uint8_t row, uint8_t col) {
  uint8_t direction = 0;
  while (direction == 0) {
    direction = rand() % 4 + 1;
    switch (direction) {
    case DIRECTION_UP:
      if ((row - 1) == 0) {
          direction = 0;
      }
    break;
    case DIRECTION_DOWN:
      if ((row + 1) == 31) {
        direction = 0;
      }
      break;
    case DIRECTION_LEFT:
      if ((col - 1) == 0) {
        direction = 0;
      }
      break;
    case DIRECTION_RIGHT:
      if ((col + 1) == 31) {
        direction = 0;
      }
      break;
    }
  }
  return direction;
}  

void expand_small_rooms(floor_t *floor) {
  uint8_t *tiles = (uint8_t *)floor->tiles;
  const uint8_t *tiles_max = tiles + MAPSIZE;
  uint8_t col = 0;
  uint8_t row = 0;
  for (; tiles < tiles_max; tiles++) {
    if (row == 0 || row == 31) {
      goto end;
    } else if (col == 0 || col == 31) {
      goto end;
    }

    if (*tiles != FLOOR_TILE) {
      goto end;
    }

    /*
      Bitflag field
      starting from 1st bit
      None Above 0
      None Below 1
      None Left  2
      None Right 3
     */
    uint8_t around_flags = 0xf;
    if ((row - 1) != 0 && *(tiles - 32) == FLOOR_TILE) {
      around_flags ^= 0x1;
    }
    if ((row + 1) != 31 && *(tiles + 32) == FLOOR_TILE) {
      around_flags ^= 0x2;
    }
    if ((col - 1) != 0 && *(tiles - 1) == FLOOR_TILE) {
      around_flags ^= 0x4;
    }      
    if ((col + 1) != 31 && *(tiles + 1) == FLOOR_TILE) {
      around_flags ^= 0x8;
    }

    if (around_flags == 0) {
      goto end;
    }      

    uint8_t offset = 0;
    /*if (around_flags % 2 != 0) {
      offset = 1;
      }*/

    uint8_t extra_tiles = around_flags;
    uint8_t max_path = around_flags % 4;
    /*for (;extra_tiles != 0; extra_tiles--) {
      direction_t direction = select_direction(row, col);
      uint8_t *temp_tiles = tiles;
      uint8_t temp_row = row;
      uint8_t temp_col = col;
      for (uint8_t path = max_path; path != 0; path--, extra_tiles--) {
        switch (direction) {
        case DIRECTION_UP:
          temp_row -= 1;
          temp_tiles -= 32;
          break;
        case DIRECTION_DOWN:
          temp_row += 1;
          temp_tiles += 32;
          break;
        case DIRECTION_LEFT:
          temp_col -= 1;
          temp_tiles -= 1;
          break;
        case DIRECTION_RIGHT:
          temp_col += 1;
          temp_tiles += 1;
          break;
        }

        *temp_tiles = FLOOR_TILE;
        direction = select_direction(temp_row, temp_col);
      }

      } */     
    
  end:
    col++;
    if (col == 32) {
      col = 0;
      row++;
    }      
  }    
}  

void generate_floor() {
  initialize_floor(&main_floor);
  add_more_floor(&main_floor);
  put_in_more_walls(&main_floor);
  //expand_small_rooms(&main_floor);
}

void draw_floor() {
  set_bkg_tiles(0, 0, 32, 32, (uint8_t*)main_floor.tiles);
  wait_vbl_done();
}  
