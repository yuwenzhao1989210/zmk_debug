
#include "eeprom.h"
#include "keycodes.h"
#include "string.h"
#include "eeconfig.h"
#include "action.h"
#include "protocol_mode.h"
#include "power_manage_qf.h"
#include "qf.h"
#include "rgb_matrix.h"


#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, L06,         R00, R01, R02, R03, R04, R05, R06, \
    L10, L11, L12, L13, L14, L15, L16,         R10, R11, R12, R13, R14, R15, R16, \
    L20, L21, L22, L23, L24, L25, L26,         R20, R21, R22, R23, R24, R25, R26, \
    L30, L31, L32, L33, L34, L35, L36,         R30, R31, R32, R33, R34, R35, R36  \
) \
{ \
    { L00, L01, L02, L03, L04, L05, L06 }, \
    { L10, L11, L12, L13, L14, L15, L16 }, \
    { L20, L21, L22, L23, L24, L25, L26 }, \
    { L30, L31, L32, L33, L34, L35, L36 }, \
    \
    { R00, R01, R02, R03, R04, R05, R06 }, \
    { R10, R11, R12, R13, R14, R15, R16 }, \
    { R20, R21, R22, R23, R24, R25, R26 }, \
    { R30, R31, R32, R33, R34, R35, R36 }  \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_Q,  KC_W, KC_E,   KC_R,  KC_T,    KC_VOLU,      KC_RCTL, KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,KC_NO,
        KC_CAPS, KC_A,  KC_S, KC_D,   KC_F,  KC_G,    KC_VOLD,     KC_RSFT, KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN,KC_NO,
        KC_LSFT, KC_Z,  KC_X, KC_C,   KC_V,  KC_B,    KC_NO,       KC_NO,   KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH,KC_NO,
        KC_LALT, KC_TAB,KC_NO,KC_LCTL,MO(1), KC_SPC,  KC_NO,       KC_ENT,  MO(2),  KC_RGUI, KC_BSPC, KC_QUOT,KC_DEL,KC_NO
    ),
        [1] = LAYOUT(
        RESET_KB,BL_SW_1,BL_SW_2, BL_SW_3, RADIO_GZ, USB_QF,  KC_VOLU,      KC_RCTL, KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,KC_NO,
        KC_CAPS, KC_A,  KC_S,     KC_D,    KC_F,     KC_G,    KC_VOLD,      KC_RSFT, KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN,KC_NO,
        KC_LSFT, KC_Z,  KC_X,     KC_C,    KC_V,     KC_B,    KC_NO,        KC_NO,   KC_N,   KC_M,    KC_COMM, KC_DOT, KC_SLSH,KC_NO,
        KC_LALT, KC_TAB,KC_NO,    KC_LCTL, MO(1),    KC_SPC,  KC_NO,        KC_ENT,  MO(2),  KC_RGUI, KC_BSPC, KC_QUOT,KC_DEL,KC_NO
    ),

    
};



#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { 
    {
        { 0,    1,   2,    3 }, 
        { 7,    6,   5,    4 }, 
        { 8,    9,  10,   11 }, 
        { 12,  13,  14,   15  }
    },{
        { 0,   60}, { 12,  60}, { 24,  60}, { 36,  60}, //4
        { 192, 48}, { 180, 48}, { 168, 48}, { 156, 48}, //4
        { 0,   36}, { 12,  36}, { 24,  36}, { 36,  36}, //4
        { 156, 24}, { 132, 24}, { 120, 24}, { 108, 24}
    }, {
        1,1,1,1,1,
        1,1,1,1,1,
        1,1,1,1,1,
        1
    } 
};
// clang-format on
#endif
void keyboard_post_init_user(void) {}

extern bool process_record_user_cb(uint16_t keycode, keyrecord_t *record) ;
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