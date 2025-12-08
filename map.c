#include <gb/gb.h>
#include <gb/hardware.h>
#include <stdint.h>
#include "map.h"
#include "noise.h"
#include <rand.h>

floor_t main_floor;



void initialize_floor(floor_t *floor) {
  uint8_t value = rand();
  const uint8_t *noise_map1 = get_noise(value);
  value = rand();
  const uint8_t *noise_map2 = get_noise(value);
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

void add_more_floor(floor_t *floor) {
  uint8_t value = rand();
  const uint8_t *noise_map1 = get_noise(value);
  value = rand();
  const uint8_t *noise_map2 = get_noise(value);
  const uint8_t threshold = WALL_THRESHOLD + (rand() % 20);
  const uint8_t *noise1_end = noise_map1 + NOISE_SIZE;
  const uint8_t *noise2_end = noise_map2 + NOISE_SIZE;
  uint8_t *tiles = (uint8_t*)floor->tiles;
  uint8_t col = 0;
  uint8_t row = 0;
  for (; noise_map1 < noise1_end; noise_map1++, noise_map2++, tiles++) {
    if (row == 0 || row == 31) {
      continue;
    } else if (col == 0 || col == 31) {
      continue;
    } else {
      if ((*noise_map1 + *noise_map2) >= threshold) {
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



void generate_floor() {
  initialize_floor(&main_floor);
  add_more_floor(&main_floor);
}

void draw_floor() {
  set_bkg_tiles(0, 0, 32, 32, (uint8_t*)main_floor.tiles);
  wait_vbl_done();
}  
