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
  wait_vbl_done();
  uint8_t x = 0 , y = 0;
  
  for (;;) {

    uint8_t joy = joypad();
    switch (joy) {
    case J_UP:
      y--;
      break;
    case J_DOWN:
      y++;
      break;
    case J_LEFT:
      x--;
      break;
    case J_RIGHT:
      x++;
      break;
    }      
    
    move_bkg(x * 8, y * 8);
    vsync();
  }    
}  
