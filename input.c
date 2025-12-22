#include <gb/gb.h>
#include <gb/hardware.h>
#include <stdint.h>
#include "input.h"

// Input state structure - tracks each button individually
typedef struct {
    uint8_t hold_time[BTN_COUNT];  // How long each button has been held
    uint8_t prev_joypad;           // Previous joypad state for edge detection
    uint8_t current_joypad;        // Current joypad state
} InputState;



InputState input_state = {{0, 0, 0, 0, 0, 0, 0, 0}, 0, 0};

// Helper function to get button mask from button index
uint8_t get_button_mask(uint8_t button_index) {
    switch (button_index) {
        case BTN_A:      return J_A;
        case BTN_B:      return J_B;
        case BTN_SELECT: return J_SELECT;
        case BTN_START:  return J_START;
        case BTN_RIGHT:  return J_RIGHT;
        case BTN_LEFT:   return J_LEFT;
        case BTN_UP:     return J_UP;
        case BTN_DOWN:   return J_DOWN;
        default:         return 0;
    }
}

// Function to update input state for all buttons
void update_input() {
    uint8_t joy = joypad();
    input_state.current_joypad = joy;
    
    // Update each button's hold time
    for (uint8_t i = 0; i < BTN_COUNT; i++) {
        uint8_t button_mask = get_button_mask(i);
        
        if (joy & button_mask) {
            // Button is pressed
            if (input_state.hold_time[i] < 255) {  // Prevent overflow
                input_state.hold_time[i]++;
            }
        } else {
            // Button is not pressed - reset hold time
            input_state.hold_time[i] = 0;
        }
    }
    
    input_state.prev_joypad = joy;
}

// Check if a button is currently pressed
uint8_t is_button_pressed(uint8_t button_index) {
    if (button_index >= BTN_COUNT) return 0;
    return input_state.hold_time[button_index] > 0;
}

// Check if a button was just pressed this frame (not held from before)
uint8_t is_button_just_pressed(uint8_t button_index) {
    if (button_index >= BTN_COUNT) return 0;
    return input_state.hold_time[button_index] == 1;
}

// Get how long a button has been held
uint8_t get_button_hold_time(uint8_t button_index) {
    if (button_index >= BTN_COUNT) return 0;
    return input_state.hold_time[button_index];
}

// Check if button was just released this frame
uint8_t is_button_just_released(uint8_t button_index) {
    if (button_index >= BTN_COUNT) return 0;
    uint8_t button_mask = get_button_mask(button_index);
    return (input_state.prev_joypad & button_mask) && !(input_state.current_joypad & button_mask);
}

DirectionState get_directional_input() {
    DirectionState result = {DIR_NONE, 0};
    
    // Check which direction buttons are pressed
    uint8_t up_pressed = is_button_pressed(BTN_UP);
    uint8_t down_pressed = is_button_pressed(BTN_DOWN);
    uint8_t left_pressed = is_button_pressed(BTN_LEFT);
    uint8_t right_pressed = is_button_pressed(BTN_RIGHT);
    
    // If multiple directions pressed, prioritize the most recently pressed
    uint8_t up_time = get_button_hold_time(BTN_UP);
    uint8_t down_time = get_button_hold_time(BTN_DOWN);
    uint8_t left_time = get_button_hold_time(BTN_LEFT);
    uint8_t right_time = get_button_hold_time(BTN_RIGHT);
    
    // Find newest input (lowest non-zero hold time)
    uint8_t min_time = 255;
    
    if (up_pressed && up_time <= min_time) {
        result.direction = DIR_UP;
        result.hold_time = up_time;
        min_time = up_time;
    }
    if (down_pressed && down_time < min_time) {
        result.direction = DIR_DOWN;
        result.hold_time = down_time;
        min_time = down_time;
    }
    if (left_pressed && left_time < min_time) {
        result.direction = DIR_LEFT;
        result.hold_time = left_time;
        min_time = left_time;
    }
    if (right_pressed && right_time < min_time) {
        result.direction = DIR_RIGHT;
        result.hold_time = right_time;
        min_time = right_time;
    }
    
    return result;
}

