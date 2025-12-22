#include <gb/gb.h>
#include <rand.h>
#include <gb/hardware.h>
#include <stdint.h>
#include "map.h"
#include "sprites.h"
#include "camera.h"
#include "character.h"
#include "input.h"
#include "player.h"

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
  tick_character_for_movement(&player.state);
  SHOW_SPRITES;
  
  DISPLAY_ON;
  wait_vbl_done();
  uint8_t x = 0, y = 0;
  for (;;) {
    wait_vbl_done();
    tick_characters_for_movement();
    update_input();
    if (is_button_just_pressed(BTN_A)) {
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
    control_player();
    //scroll_camera(delta_x, delta_y);
    update_map_display();
  }    
}  
