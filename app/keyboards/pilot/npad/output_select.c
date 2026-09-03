#include "output_select.h"
#include <stdint.h>
#include "protocol_mode.h"
#include "eeprom.h"
#include "report.h"
#include "nrf_sdh.h"

static volatile uint8_t usb_ind = 0;

extern volatile bool usb_enabled_qf;

uint8_t curr_mode = 99;

void usb_send_keyboard(report_keyboard_t *report);

/*

#define MXKBD_USB_MODE      0U
#define MXKBD_BLE_MODE      1U
#define MXKBD_BLE_CHANNEL_1 1U
#define MXKBD_BLE_CHANNEL_2 2U
#define MXKBD_BLE_CHANNEL_3 3U
#define MXKBD_BLE_CHANNEL_4 4U
#define MXKBD_BLE_CHANNEL_5 5U
#define MXKBD_BLE_CHANNEL_6 6U
#define MXKBD_GZLL_MODE     7U
#define ESB_MODE      8U

*/
uint8_t is_ble_mode(void) {
    uint8_t currMode = get_current_protocol_mode();

    if (currMode > 0 && currMode <= 8) {
        return 1;
    }

    return 0;
}

uint8_t is_gz_mode(void) {
    uint8_t currMode = get_current_protocol_mode();

    if (currMode == GZ_MODE) {
        return 1;
    }

    return 0;
}

extern uint8_t read_mode(void);

extern volatile bool usb_enabled_qf;
// uint8_t read_ram_mode(void) {
//     if (curr_mode == 99) {
//         curr_mode = read_mode();
//     }
//     return curr_mode;
// }

static void delayed_reset(void *p_event_data, uint16_t event_size) { NVIC_SystemReset(); }

extern volatile bool usb_enabled_qf;
void change_send_mode(uint8_t next_mode) {}
