// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _FN1,
    _FN2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9, 
        KC_P4,   KC_P5,   KC_P6  
    ),
    [1] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO, 
        KC_NO,   KC_NO,   KC_NO
    ), 

    [2] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO, 
        KC_NO,   KC_NO,   KC_NO)
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // First encoder
        if(IS_LAYER_ON(1)) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } 
            else {
                tap_code(KC_VOLD);
            }
    }
        if(IS_LAYER_ON(1)) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } 
            else {
                tap_code(KC_VOLD);
            }
    }
}

#ifdef OLED_ENABLE

// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//     return OLED_ROTATION_270;
}
bool oled_task_user(void) {
    oled_setcursor(0, 1);
    oled_write("HackPad 101\n", false);
    oled_setcursor(0, 11);
    
    
    // layer
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write("Layer: Base\n", false);
            break;
        case _FN1:
            oled_write("Layer: Fn 1\n", false);
            break;
        case _FN2:
            oled_write("Layer: Fn 2\n", false);
            break;
        default:
            oled_write("Layer: Unknown\n", false);
    }

    //caps lock
    oled_setcursor(100, 1);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("CAPS: ON") : PSTR("CAPS: OFF"), false);
    return false;

    //image
    //static const char PROGMEM hackpad101_logo[] = {
    // paste the byte array here (imang to byte array converter)
}
#endif