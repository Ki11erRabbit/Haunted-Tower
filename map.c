#include <gb/gb.h>
#include <gb/hardware.h>
#include <stdint.h>
#include "map.h"
#include "noise.h"
#include "map.h"
#include <rand.h>

#define MAXSMALL_ROOMS 16


floor_t main_floor;


const palette_color_t floor_red[4] = {
    RGB8(255, 255, 255), RGB8(255, 88, 86), RGB8(255, 3, 41), RGB8(100, 26, 24),
};    
const palette_color_t floor_green[4] = {
    RGB8(255, 255, 255), RGB8(152, 255, 149), RGB8(40, 255, 56), RGB8(20, 91, 20),
};    
const palette_color_t floor_blue[4] = {
    RGB8(255, 255, 255), RGB8(118, 119, 255), RGB8(40, 45, 255), RGB8(19, 21, 122),
};    
const palette_color_t floor_grey[4] = {
    RGB8(255, 255, 255), RGB8(200, 200, 200), RGB8(117, 117, 117), RGB8(24, 24, 24),
};    
const palette_color_t floor_purple[4] = {
    RGB8(255, 255, 255), RGB8(195, 159, 255), RGB8(146, 83, 245), RGB8(82, 51, 143),
};

const palette_color_t *select_floor_color(uint8_t selector) {
  switch (selector % 5) {
  case 0:
      return floor_red;
  case 1:
      return floor_green;
  case 2:
      return floor_blue;
  case 3:
      return floor_grey;
  case 4:
      return floor_purple;
  }
  return 0;
}

void random_floor_color(void) {
    uint8_t value = rand();
    const palette_color_t *pallet = select_floor_color(value);
    set_bkg_palette(0, 1, pallet);
}  

/*
 * This function creates the initial layout of a floor.
 * We randomly select either perlin or voronoi noise for this.
 * If the noise value is >= WALL_THRESHOLD, then it is a wall,
 * otherwise it is a floor tile.
 */
void initialize_floor(floor_t *floor) {
  uint8_t value = rand();
  const uint8_t *noise_map1 = get_voronoi_noise(value);
  value = rand();
  const uint8_t *noise1_end = noise_map1 + NOISE_SIZE;
  uint8_t *tiles = (uint8_t*)floor->tiles;
  uint8_t col = 0;
  uint8_t row = 0;
  for (; noise_map1 < noise1_end; noise_map1++, tiles++) {
    if (row == 0 || row == 31) {
      *tiles = WALL_TILE;
    } else if (col == 0 || col == 31) {
      *tiles = WALL_TILE;
    } else {
      if (*noise_map1 >= WALL_THRESHOLD) {
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

/*
 * This function uses perlin noise to try to add more walls to a floor.
 * We offset the WALL_THRESHOLD a little to add more randomness.
 * Then, if the value at the position in the noisemap is <= threshold
 * then we set that tile to a wall.
 */
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

/*
 * This function uses voronoi noise to try to expand the amount of flooring.
 * We offset the FLOOR_THRESHOLD with a number 0..20 to add more randomness.
 * Then if the noise any position is <= threshold, then it is made into a floor tile.
 */
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

/*
 * This function's goal is to remove random floating walls.
 * It checks for the amount of free spaces around a wall tile.
 */
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


/*
 * This function's goal is to try to remove open spaces that
 * are completely surrounded by walls that may make actor placement harder.
 * It checks around floor tiles.
 * It doesn't work very well but not sure how to improve it.
 */
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
    uint8_t diagonal_neighbors = 0;
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

    if (neighbors >= 5 && diagonal_neighbors <= 2) {
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

/*
 * This Pass applies a celluar automaton check to tiles.
 * This is so that jagged edges and individual walls get cleaned up.
 */
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

void generate_floor(void) {
  cpu_fast();
  initialize_floor(&main_floor);
  wall_liveness(&main_floor);
  put_in_more_walls(&main_floor);
  //add_more_floor(&main_floor);
  smooth_walls(&main_floor);
  remove_holes(&main_floor);
  wall_liveness(&main_floor);
  //remove_holes(&main_floor);
  //remove_holes(&main_floor);
  cpu_slow();
}

/*void draw_floor(void) {
  set_bkg_tiles(0, 0, 32, 32, (uint8_t*)main_floor.tiles);
  wait_vbl_done();
  }  */
