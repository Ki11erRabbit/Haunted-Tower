#include <stdint.h>
#include <gb/hardware.h>
#include "map.h"
#include "noise.h"

floor_t main_floor;


void initialize_floor(floor_t *floor) {
  uint8_t timer = TIMA_REG;
  const uint8_t *noise_map;
  switch (timer % 4) {
  case 0:
    noise_map = perlin_noise0;
    break;
  case 1:
    noise_map = perlin_noise1;
    break;
  case 2:
    noise_map = perlin_noise2;
    break;
  case 3:
    noise_map = perlin_noise3;
    break;
  }
  const uint8_t *noise_end = noise_map + NOISE_SIZE;
  uint8_t *tiles = (uint8_t*)floor->tiles;
  uint8_t col = 0;
  uint8_t row = 0;
  for (; noise_map < noise_end; noise_map++, tiles++) {
    if (row == 0 || row == 31) {
      *tiles = WALL_TILE;
    } else if (col == 0 || col == 31) {
      *tiles = WALL_TILE;
    } else {
      if (*noise_map >= WALL_THRESHOLD) {
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
