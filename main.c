#include <gb/gb.h>
#include <stdint.h>
#include "map.h"
#include "sprites.h"


void main() {
  DISPLAY_OFF;
  set_bkg_data(0, 5, basespritesTiles);
  initialize_floor(&main_floor);
  set_bkg_tiles(0, 0, 32, 32, (uint8_t *)main_floor.tiles);
  SHOW_BKG;
  DISPLAY_ON;
  for (;;) {
    wait_vbl_done();

  }    
}  
