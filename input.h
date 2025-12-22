#ifndef HT_INPUT_H
#define HT_INPUT_H

// Button index constants
#define BTN_A      0
#define BTN_B      1
#define BTN_SELECT 2
#define BTN_START  3
#define BTN_RIGHT  4
#define BTN_LEFT   5
#define BTN_UP     6
#define BTN_DOWN   7
#define BTN_COUNT  8

#define DIR_NONE  0
#define DIR_UP    1
#define DIR_DOWN  2
#define DIR_LEFT  3
#define DIR_RIGHT 4

// Directional input helpers with priority for new inputs
typedef struct {
    uint8_t direction;  // Current active direction
    uint8_t hold_time;  // Hold time for this direction
} DirectionState;

uint8_t get_button_mask(uint8_t button_index);

// Function to update input state for all buttons
void update_input(); 

// Check if a button is currently pressed
uint8_t is_button_pressed(uint8_t button_index);

// Check if a button was just pressed this frame (not held from before)
uint8_t is_button_just_pressed(uint8_t button_index);

// Get how long a button has been held
uint8_t get_button_hold_time(uint8_t button_index);

// Check if button was just released this frame
uint8_t is_button_just_released(uint8_t button_index);

DirectionState get_directional_input();

#endif
