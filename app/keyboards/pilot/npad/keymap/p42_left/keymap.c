
#include "eeprom.h"
#include "keycodes.h"
#include "string.h"
#include "eeconfig.h"
#include "action.h"
#include "protocol_mode.h"
#include "power_manage_qf.h"
#include "qf.h"
#include "rgb_matrix.h"

#define LAYOUT_split_ortho_numpad( \
    k00, k01, k02, k03, k04, k05,   k06, k07, k08, k09, k0a,   n00, n01, n02, n03, \
    k10, k11, k12, k13, k14, k15,   k16, k17, k18, k19, k1a,   n10, n11, n12, n13, \
    k20, k21, k22, k23, k24, k25,   k26, k27, k28, k29, k2a,   n20, n21, n22, n23, \
    k30, k31, k32, k33, k34, k35,   k36, k37, k38, k39, k3a,   n30, n31, n32, n33  \
) { \
    { k00, k01, k02, k03, k04, k05,   k06, k07, k08, k09, k0a }, \
    { k10, k11, k12, k13, k14, k15,   k16, k17, k18, k19, k1a }, \
    { k20, k21, k22, k23, k24, k25,   k26, k27, k28, k29, k2a }, \
    { k30, k31, k32, k33, k34, k35,   k36, k37, k38, k39, k3a }, \
    { n00, n01, n02, n03, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { n10, n11, n12, n13, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { n20, n21, n22, n23, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { n30, n31, n32, n33, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }  \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [0] = LAYOUT_split_ortho_numpad(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_PSLS, KC_PAST, KC_PPLS, KC_PMNS,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_ENTER,  KC_P7,   KC_P8,   KC_P9,   KC_P0,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_UP,   MO(1),     KC_P4,   KC_P5,   KC_P6,   KC_KP_DOT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_NO,   KC_NO,    KC_SPC,  KC_LEFT, KC_DOWN, KC_RIGHT,KC_BSPC,   KC_P1,   KC_P2,   KC_P3,   KC_KP_ENTER
    ),
  [1] = LAYOUT_split_ortho_numpad(
        RESET_KB,BL_SW_1, BL_SW_2, BL_SW_3, RADIO_GZ, USB_QF,     KC_Y,    KC_U,    KC_I,    KC_VOLD, KC_VOLU,   KC_PSLS, KC_PAST, KC_PPLS, KC_PMNS,
        KC_TAB,  RGB_RMOD,RGB_MOD, RGB_TOG, KC_F,     KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_ENTER,  KC_P7,   KC_P8,   KC_P9,   KC_P0,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,     KC_N,    KC_M,    KC_COMM, KC_UP,   KC_NO,     KC_P4,   KC_P5,   KC_P6,   KC_KP_DOT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_NO,    KC_NO,    KC_SPC,  KC_LEFT, KC_DOWN, KC_RIGHT,KC_BSPC,   KC_P1,   KC_P2,   KC_P3,   KC_KP_ENTER
    )
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