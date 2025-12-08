#include <gb/gb.h>
#include <rand.h>
#include <gb/hardware.h>
#include <stdint.h>
#include "map.h"
#include "sprites.h"

void main(void) {
  initrand(DIV_REG + LY_REG);
  DISPLAY_OFF;

  set_default_palette();

  set_bkg_data(0, 5, basespritesTiles);
 
  generate_floor();
  draw_floor();
  SHOW_BKG;
  DISPLAY_ON;
  wait_vbl_done();
  uint8_t x = 0, y = 0;
  for (;;) {

    uint8_t joy = joypad();
    switch (joy) {
    case J_UP:
      if (y != 0) {
        y--;
      }        
      break;
    case J_DOWN:
      y++;
      if (y >= 15) {
        y = 14;
      }        
      break;
    case J_LEFT:
      if (x != 0) {
        x--;
      }        
      break;
    case J_RIGHT:
      x++;
      if (x >= 13) {
        x = 12;
      }
      break;
    case J_A:
      DISPLAY_OFF;
      generate_floor();
      draw_floor();
      DISPLAY_ON;
      break;
    }
    
    move_bkg(x * 8, y * 8);
    vsync();
  }    
}  
