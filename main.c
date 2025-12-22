#include <gb/gb.h>
#include <rand.h>
#include <gb/hardware.h>
#include <stdint.h>
#include "map.h"
#include "sprites.h"
#include "camera.h"
#include "character.h"

void main(void) {
  initrand(DIV_REG + LY_REG);
  DISPLAY_OFF;

  set_default_palette();
  random_floor_color();

  set_bkg_data(0, 18, BackgroundTiles);
 
  generate_floor();
  // draw_floor();
  initial_draw();
  SHOW_BKG;

  init_player();
  SHOW_SPRITES;
  
  DISPLAY_ON;
  wait_vbl_done();
  uint8_t x = 0, y = 0;
  for (;;) {
    wait_vbl_done();
    tick_characters_for_movement();
    uint8_t joy = joypad();
    int8_t delta_x = 0;
    int8_t delta_y = 0;
    switch (joy) {
    case J_UP:
        delta_y = -1;
        break;
    case J_DOWN:
        delta_y = 1;
        break;
    case J_LEFT:
        delta_x = -1;
        break;
    case J_RIGHT:
        delta_x = 1;
        break;
    case J_A:
      DISPLAY_OFF;
      generate_floor();
      random_floor_color();
      reset_camera_state();
      initial_draw();
      NEXT_PLAYER_COLOR(player);
      set_player_color();
      DISPLAY_ON;
      break;
    }
    scroll_camera(delta_x, delta_y);
    update_map_display();
    vsync();
  }    
}  
