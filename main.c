#include <gb/gb.h>
#include <rand.h>
#include <gb/hardware.h>
#include <stdint.h>
#include "map.h"
#include "sprites.h"
#include "camera.h"

void main(void) {
  initrand(DIV_REG + LY_REG);
  DISPLAY_OFF;

  set_default_palette();

  set_bkg_data(0, 18, BackgroundTiles);
 
  generate_floor();
  // draw_floor();
  initial_draw();
  SHOW_BKG;
  DISPLAY_ON;
  wait_vbl_done();
  uint8_t x = 0, y = 0;
  for (;;) {

    uint8_t joy = joypad();
    switch (joy) {
    case J_UP:
        if (camera.y > 0) {
            camera.y--;
        }
      break;
    case J_DOWN:
        if (camera.y < MAP_SIDE - (TILE_HEIGHT >> 1)) {
            camera.y++;
        }
      break;
    case J_LEFT:
        if (camera.x > 0) {
            camera.x--;
        }
      break;
    case J_RIGHT:
        if (camera.x < MAP_SIDE - (TILE_WIDTH >> 1)) {
            camera.x++;
        }
      break;
    case J_A:
      DISPLAY_OFF;
      generate_floor();
      initial_draw();
      DISPLAY_ON;
      break;
    }

    update_map_display();
    vsync();
  }    
}  
