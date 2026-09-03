
#include "eeprom.h"
#include "keycodes.h"
#include "string.h"
#include "eeconfig.h"
#include "action.h"
#include "protocol_mode.h"
#include "power_manage_qf.h"
#include "qf.h"
#include "rgb_matrix.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = {
           {KC_PSLS, KC_PAST, KC_PPLS, KC_PMNS, },
           {KC_P7,   KC_P8,   KC_P9,   KC_P0},
           {KC_P4,   KC_P5,   KC_P6,   KC_KP_DOT},
           {KC_P1,   KC_P2,   KC_P3,   KC_KP_ENTER}
        },    
        [1] = {

           {KC_PSLS, KC_PAST, KC_PPLS, KC_PMNS, },
           {KC_P7,   KC_P8,   KC_P9,   KC_P0},
           {KC_P4,   KC_P5,   KC_P6,   KC_KP_DOT},
           {KC_P1,   KC_P2,   KC_P3,   KC_KP_ENTER}
        },
    };

#ifdef RGB_MATRIX_ENABLE
    // clang-format off
// led_config_t g_led_config = { 
//     {
//         { 0,    1,   2,    3 }, 
//         { 7,    6,   5,    4 }, 
//         { 8,    9,  10,   11 }, 
//         { 12,  13,  14,   15  }
//     },{
//         { 0,   60}, { 12,  60}, { 24,  60}, { 36,  60}, //4
//         { 192, 48}, { 180, 48}, { 168, 48}, { 156, 48}, //4
//         { 0,   36}, { 12,  36}, { 24,  36}, { 36,  36}, //4
//         { 156, 24}, { 132, 24}, { 120, 24}, { 108, 24}
//     }, {
//         1,1,1,1,1,
//         1,1,1,1,1,
//         1,1,1,1,1,
//         1
//     } 
// };
// clang-format on
#endif
// void keyboard_post_init_user(void) {
// }
void keyboard_post_init_user(void) {}
extern bool process_record_user_cb(uint16_t keycode, keyrecord_t *record);
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
    case KC_CAPS:
        if (record->event.pressed) {
            //  NRF_LOG_INFO("caps unlocked\n");
        }
        break;
    }

    return process_record_user_cb(keycode, record);
}

bool is_keyboard_master(void) {
    return true;
}