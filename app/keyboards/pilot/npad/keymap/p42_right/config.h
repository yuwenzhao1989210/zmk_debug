#pragma once


#include "rgb_qf.h"

#define GPIO(port, pin) ((port << 5) | pin) 
/* key matrix size */
#define DIODE_DIRECTION  COL2ROW

#define DEBOUNCE  5

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
// #define EECONFIG_QF_RESET_CODE (uint8_t *)44

#define DYNAMIC_KEYMAP_LAYER_COUNT 16

#define DEVICE_NAME_0                   "Z16 BLE 1"                         /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_1                   "Z16 BLE 2"                         /**< Name of device. Will be included in the advertising data. */
#define DEVICE_NAME_2                   "Z15 BLE 3"     
// #define VIAL_KEYBOARD_UID {0x6C, 0xD9, 0xA6, 0x5A, 0xE8, 0xA3, 0x7A, 0x8B}
#define VIAL_KEYBOARD_UID { 0xCD, 0x09, 0x03, 0x02, 0x20, 0xF5, 0x28, 0x33 }
#define RAW_HID_ENABLE

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define MATRIX_ROWS 4
#define MATRIX_COLS 4

#define THIS_DEVICE_ROWS MATRIX_ROWS
#define THIS_DEVICE_COLS 4

#define MATRIX_ROW_PINS { 20, 17, 0, 4}
#define MATRIX_COL_PINS { 15, 31, 30, 29}


#define LED_PIN GPIO(0,20)
#define POWER_PIN GPIO(0,3)

#define CAPS_LOCK_IO GPIO(0,30)

#define USE_BATTERY_PIN NRF_SAADC_INPUT_AIN0
#define BATTERY_VMAX 4100
#define TAP_CODE_DELAY 10

#define STATE_LED_ACTIVE 1

#define STATE_LED NRF_GPIO_PIN_MAP(0, 2)
#define STATE_LED_01 NRF_GPIO_PIN_MAP(0, 28)
#define STATE_LED_02 NRF_GPIO_PIN_MAP(0, 3)
#define STATE_LED_03 NRF_GPIO_PIN_MAP(0, 2)

#define LED_BLINK_FAST_INTERVAL APP_TIMER_TICKS(100)
#define LED_BLINK_FAST_INTERVAL_RGB APP_TIMER_TICKS(3000)
#define LED_BLINK_SLOW_INTERVAL APP_TIMER_TICKS(2000)
#define DFU_MAGIC_SKIP                  0x6d


#define RGB_MATRIX_LED_COUNT 16
#define A11 11

#define BATTERY_PIN NRF_SAADC_INPUT_VDDHDIV5 
#define  QF_BATTERY_ENABLE

#define QF_3V3

#define BLE_SYSTEM_OFF_SEC 1800

#define BLE_BLINK_LED_ENABLE
#define SLEEP_COUNTER_MAX 1

#define RGB_MATRIX_WS2812
#define QF_TX_POWER 4

#define MUL_QF_SKIP_HEARTBEAT
#define ESB_QF_PIP_0_1

#define ADC_MAX_VALUE 940  // 12-bit ADC 最大值为 950
#define RGB_MATRIX_WS2812
#define QF_595_ENABLED

#define SPLIT_KEYBOARD
#define SPLIT_PERIPHERAL

#define ROWS_PER_HAND MATRIX_ROWS/2

#undef NRF_STATIC_INLINE
#define NRF_STATIC_INLINE __STATIC_INLINE
// #define NRF_LOG_INFO(...)    printTMP(__VA_ARGS__)
#define C_R_TO_POSITION_QF
void NRF_LOG_INFO(const char *fmt, ...);

#define QMK_BUILDDATE "2026-06-29-00:00:00"