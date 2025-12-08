#include <gb/gb.h>
#include <rand.h>
#include <gb/hardware.h>
#include <stdint.h>
#include "map.h"
#include "sprites.h"



void main() {
  initrand(DIV_REG + LY_REG);
  DISPLAY_OFF;


  BCPS_REG = 0x80;  // Auto-increment, palette 0, color 0
  BCPD_REG = 0xFF;  // White - low byte
  BCPD_REG = 0x7F;  // White - high byte
  BCPD_REG = 0x94;  // Light gray - low byte
  BCPD_REG = 0x52;  // Light gray - high byte
  BCPD_REG = 0x4A;  // Dark gray - low byte
  BCPD_REG = 0x29;  // Dark gray - high byte
  BCPD_REG = 0x00;  // Black - low byte
  BCPD_REG = 0x00;  // Black - high byte


  set_bkg_data(0, 5, basespritesTiles);
 
  generate_floor();
  draw_floor();
  SHOW_BKG;
  DISPLAY_ON;
  wait_vbl_done();
  uint8_t x = 0 , y = 0;
  
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
