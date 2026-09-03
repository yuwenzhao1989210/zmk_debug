#pragma once


#include "rgb_qf.h"

#define GPIO(port, pin) ((port << 5) | pin) 
/* key matrix size */
#define DIODE_DIRECTION  COL2ROW

#define BLE_SLEEP_OFF_TIMEOUT 1800  // power off time , then shutdown    30min
#define RADIO_SLEEP_OFF_TIMEOUT 40  // power off time , then shutdown    40 * 125ms = 5000ms

#define DEBOUNCE  5

#undef EECONFIG_KB_DATA_SIZE
#define EECONFIG_KB_DATA_SIZE 10
#define EEPROM_SIZE 4096 
// #define EECONFIG_BASE_SIZE 37
#define EECONFIG_DFU_FLAG  (uint8_t *)37
#define EECONFIG_SEND_MODE  (uint8_t *)38
#define EECONFIG_MODE0_PEER  (uint8_t *)39
#define EECONFIG_MODE1_PEER  (uint8_t *)40
#define EECONFIG_MODE2_PEER  (uint8_t *)41

#define EECONFIG_CLI_MODE (uint8_t *)42
#define EECONFIG_RGB_MATRIX_STATUS2 (uint8_t *)43

#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

#define DEVICE_NAME_0                   "WCorne BLE"                         /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_1                   "WCorne BLE"                         /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_2                   "WCorne BLE"                         /**< Name of device. Will be included in the advertising data. */

// #define VIAL_KEYBOARD_UID {0x6C, 0xD9, 0xA6, 0x5A, 0xE8, 0xA3, 0x7A, 0x8B}
#define VIAL_KEYBOARD_UID { 0xCD, 0x09, 0x03, 0x02, 0x20, 0xF5, 0x28, 0x33 }
#define RAW_HID_ENABLE

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define MATRIX_ROWS 8
#define MATRIX_COLS 7

#define THIS_DEVICE_ROWS MATRIX_ROWS
#define THIS_DEVICE_COLS MATRIX_COLS

// #define MATRIX_ROW_PINS { 8, 9, 15, 17,}
//#define MATRIX_COL_PINS { 1, 2, 3, 4,6,  7,   }

#define MATRIX_ROW_PINS { 29, 31, 1, 20}
#define MATRIX_COL_PINS { 2, 28, 30, 15,17,  0,11}

#define LED_PIN GPIO(0,24)
#define POWER_PIN GPIO(0,3)

// #define CAPS_LOCK_IO GPIO(1,2)

#define USE_BATTERY_PIN NRF_SAADC_INPUT_AIN0
#define BATTERY_VMAX 4100
// #define TAP_CODE_DELAY 5

#define STATE_LED_ACTIVE 1

#define STATE_LED NRF_GPIO_PIN_MAP(0, 4)
#define STATE_LED_01 NRF_GPIO_PIN_MAP(0, 4)
#define STATE_LED_02 NRF_GPIO_PIN_MAP(0, 4)
#define STATE_LED_03 NRF_GPIO_PIN_MAP(0, 4)

#define LED_BLINK_FAST_INTERVAL APP_TIMER_TICKS(100)
#define LED_BLINK_FAST_INTERVAL_RGB APP_TIMER_TICKS(3000)
#define LED_BLINK_SLOW_INTERVAL APP_TIMER_TICKS(2000)
#define DFU_MAGIC_SKIP                  0x6d

#define RGB_MATRIX_LED_COUNT 8
#define A11 5

#define BATTERY_PIN NRF_SAADC_INPUT_VDDHDIV5 
#define  QF_BATTERY_ENABLE

#define QF_3V3


#define BLE_BLINK_LED_ENABLE
#undef SLEEP_COUNTER_MAX
#define SLEEP_COUNTER_MAX 100
#define QF_RGB_ENABLED

// #define NO_ACTION_TAPPING
#define RGB_MATRIX_WS2812
// #define MOUSE_ENABLE
#undef QF_TX_POWER
#define QF_TX_POWER 4

#define ESB_QF_PIP_0_1
#define ADC_MAX_VALUE 940  // 12-bit ADC 最大值为 950

//(432K->464K) wear_leveling_config.h 32K大小

#define WEAR_LEVELING_BACKING_SIZE (4096 * 8)
#define WEAR_LEVELING_LEGACY_EMULATION_BASE_PAGE_ADDRESS 0x6C000
#define WEAR_LEVELING_LEGACY_EMULATION_PAGE_COUNT 8

#undef VIAL_ENABLE
#define VIAL_ENABLE

#define SPLIT_KEYBOARD
#define SPLIT_QF_CENTER
#define ROWS_PER_HAND MATRIX_ROWS/2

#undef NRF_STATIC_INLINE
#define NRF_STATIC_INLINE __STATIC_INLINE
// #define NRF_LOG_INFO(...)    printTMP(__VA_ARGS__)

void NRF_LOG_INFO(const char *fmt, ...);

#define MATRIX_COLS_OTHER_HAND 7

// #define QF_BLINK_LEDrfvrfvrfvfv
// #define QMK_BUILDDATE "2026-06-29-00:00:00"