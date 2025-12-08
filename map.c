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
  const uint8_t *noise_map1 = get_voronoi_noise(value);
  value = rand();
  //const uint8_t *noise_map2 = get_perlin_noise(value);
  const uint8_t threshold = WALL_THRESHOLD - (rand() % 20);
  const uint8_t *noise1_end = noise_map1 + NOISE_SIZE;
  //const uint8_t *noise2_end = noise_map2 + NOISE_SIZE;
  uint8_t *tiles = (uint8_t*)floor->tiles;
  uint8_t col = 0;
  uint8_t row = 0;
  for (; noise_map1 < noise1_end; noise_map1++, tiles++) {
    if (row == 0 || row == 31) {
      *tiles = WALL_TILE;
    } else if (col == 0 || col == 31) {
      *tiles = WALL_TILE;
    } else {
      if ((*noise_map1) >= WALL_THRESHOLD) {
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
  const uint8_t *noise_map = get_perlin_noise(value);
  const uint8_t threshold = WALL_THRESHOLD - (rand() % 40);
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
      if (*noise_map <= threshold) {
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
  const uint8_t *noise_map = get_voronoi_noise(value);
  const uint8_t threshold = FLOOR_THRESHOLD + (rand() % 20);
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
      if (*noise_map <= threshold) {
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

void smooth_walls(floor_t *floor) {
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

    if (*tiles != WALL_TILE) {
      goto end;
    }
    uint8_t free_spaces = 0;
    // Above
    if (*(tiles - 32) == FLOOR_TILE) {
      free_spaces++;
    }
    // Below
    if (*(tiles + 32) == FLOOR_TILE) {
      free_spaces++;
    }
    // Left
    if (*(tiles - 1) == FLOOR_TILE) {
      free_spaces++;
    }
    // Right
    if (*(tiles + 1) == FLOOR_TILE) {
      free_spaces++;
    }
    uint8_t free_diagonals = 0;
    // Top Left
    if (*(tiles - 33) == FLOOR_TILE) {
      free_diagonals++;
    }
    // Bottom Right
    if (*(tiles + 33) == FLOOR_TILE) {
      free_diagonals++;
    }
    // Top Right
    if (*(tiles - 31) == FLOOR_TILE) {
      free_diagonals++;
    }
    // Bottom Left
    if (*(tiles + 31) == FLOOR_TILE) {
      free_diagonals++;
    }

    if (free_spaces >= 2 && free_diagonals <= 1) {
      *tiles = FLOOR_TILE;
    } else if (free_diagonals >= 2 && free_spaces <= 1) {
      *tiles = FLOOR_TILE;
    }      
    
  end:
    col++;
    if (col == 32) {
      col = 0;
      row++;
    }      
  }    
}  

void remove_holes(floor_t *floor) {
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
    uint8_t neighbors = 0;
    // Above
    if (*(tiles - 32) != FLOOR_TILE) {
      neighbors++;
    }
    // Below
    if (*(tiles + 32) != FLOOR_TILE) {
      neighbors++;
    }
    // Left
    if (*(tiles - 1) != FLOOR_TILE) {
      neighbors++;
    }
    // Right
    if (*(tiles + 1) != FLOOR_TILE) {
      neighbors++;
    }
    uint8_t diagonal_neighbors;
    // Top Left
    if (*(tiles - 33) != FLOOR_TILE) {
      diagonal_neighbors++;
      neighbors++;
    }
    // Bottom Right
    if (*(tiles + 33) != FLOOR_TILE) {
      diagonal_neighbors++;
      neighbors++;
    }
    // Top Right
    if (*(tiles - 31) != FLOOR_TILE) {
      diagonal_neighbors++;
      neighbors++;
    }
    // Bottom Left
    if (*(tiles + 31) != FLOOR_TILE) {
      diagonal_neighbors++;
      neighbors++;
    }

    if (neighbors >= 4 && diagonal_neighbors <= 5) {
      *tiles = WALL_TILE;
    }      
    
  end:
    col++;
    if (col == 32) {
      col = 0;
      row++;
    }      
  }    
}

void wall_liveness(floor_t *floor) {
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
    uint8_t is_floor = 0;
    uint8_t is_wall = 0;
    if (*tiles == FLOOR_TILE) {
      is_floor = 1;
    } else if (*tiles == WALL_TILE) {
      is_wall = 1;
    } else {
      goto end;
    }      
    uint8_t side_neighbors = 0;
    // Above
    if (*(tiles - 32) == WALL_TILE) {
      side_neighbors++;
    }
    // Below
    if (*(tiles + 32) == WALL_TILE) {
      side_neighbors++;
    }
    // Left
    if (*(tiles - 1) == WALL_TILE) {
      side_neighbors++;
    }
    // Right
    if (*(tiles + 1) == WALL_TILE) {
      side_neighbors++;
    }
    uint8_t diagonal_neighbors = 0;
    // Top Left
    if (*(tiles - 33) == WALL_TILE) {
      diagonal_neighbors++;
    }
    // Bottom Right
    if (*(tiles + 33) == WALL_TILE) {
      diagonal_neighbors++;
    }
    // Top Right
    if (*(tiles - 31) == WALL_TILE) {
      diagonal_neighbors++;
    }
    // Bottom Left
    if (*(tiles + 31) == WALL_TILE) {
      diagonal_neighbors++;
    }

    uint8_t total_neighbors = side_neighbors + diagonal_neighbors;

    if (is_floor && total_neighbors == 3 && side_neighbors >= 2) {
      *tiles = WALL_TILE;
    } else if (is_wall && (total_neighbors <= 2 || (side_neighbors <= 2 && diagonal_neighbors > 3))) {
      *tiles = FLOOR_TILE;
    }      
    
  end:
    col++;
    if (col == 32) {
      col = 0;
      row++;
    }      
  }    
}  

void generate_floor() {
  cpu_fast();
  initialize_floor(&main_floor);
  wall_liveness(&main_floor);
  put_in_more_walls(&main_floor);
  add_more_floor(&main_floor);
  smooth_walls(&main_floor);
  remove_holes(&main_floor);
  wall_liveness(&main_floor);
  //remove_holes(&main_floor);
  //remove_holes(&main_floor);
  cpu_slow();
}

void draw_floor() {
  set_bkg_tiles(0, 0, 32, 32, (uint8_t*)main_floor.tiles);
  wait_vbl_done();
}  
