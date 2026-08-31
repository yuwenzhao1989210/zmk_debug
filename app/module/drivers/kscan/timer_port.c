
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "timer.h"
#include "zephyr/logging/log.h"
#include "zmk/endpoints_types.h"
#include <zmk/ble.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

// #ifdef QF_BLINK_LED
static struct k_timer led_timer;
// static const struct gpio_dt_spec led_gpio = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec led_gpio1 = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);
static const struct gpio_dt_spec led_gpio2 = GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios);

static bool led_on = false;
static uint32_t blink_interval_ms = 500;

uint8_t read_ram_mode(void) {
    enum zmk_transport t = zmk_endpoint_get_preferred_transport();

    if (t == ZMK_TRANSPORT_USB) {
        return 0; // 0 is usb
    }

#if IS_ENABLED(CONFIG_ZMK_BLE)
    int p = zmk_ble_active_profile_index();

    if (p == 0) {
        return 1;
    }

    if (p == 1) {
        return 2;
    }

    if (p == 2) {
        return 3;
    }
#endif

    return 0;
}

static void led_gpio_on(void) {
    // int p = read_ram_mode();
    // if (p == 1) { // 1是蓝牙1
    //     gpio_pin_set_dt(&led_gpio1, 1);
    // } else if (p == 2) {
    //     LOG_INF("p==2, eset led1 ....");
    //     gpio_pin_set_dt(&led_gpio1, 1);
    // } else if (p == 3) {
    //     LOG_INF("p==3, eset led2 ....");
    gpio_pin_set_dt(&led_gpio1, 1);
}
static void led_gpio_off(void) {
    int p = read_ram_mode();

    // gpio_pin_set_dt(&led_gpio, 0); //led0 has been configured as
    // NUMLOCK INDICATOR in pad17air.overlay
    gpio_pin_set_dt(&led_gpio1, 0);
    gpio_pin_set_dt(&led_gpio2, 0);
}
// #endif
void led_set_off(void) {
    // #ifdef QF_BLINK_LED
    // if(led_on == false){
    //     return;
    // }
    LOG_INF("led_set_off 333333....");
    k_timer_stop(&led_timer);
    led_gpio_off();
    led_on = false;
    // #endif
}

void timer_init(void) { timer_clear(); }

void timer_clear(void) {}

uint32_t timer_read32(void) { return k_uptime_get_32(); }
uint16_t timer_read(void) { return (uint16_t)timer_read32(); }

uint16_t timer_elapsed(uint16_t last) { return TIMER_DIFF_16(timer_read(), last); }

uint32_t timer_elapsed32(uint32_t last) { return TIMER_DIFF_32(timer_read32(), last); }

// #ifdef QF_BLINK_LED
static uint32_t blink_cnt;
static const uint32_t blink_max = 200; // 闪 10 次 ≈ 5s @500ms
extern int zmk_ble_adv_stop(void);
extern int get_adv_status(void);
static void led_timer_handler(struct k_timer *timer) {
    led_on = !led_on;

    if (led_on) {
        led_gpio_on();
    } else {
        led_gpio_off();
    }

    if (++blink_cnt >= blink_max) {
        LOG_INF("more than %d will stop adving.... currest adv status = %d", blink_max,
                get_adv_status());
        // zmk_ble_adv_stop();
        led_set_off();
        blink_cnt = 0;
    }
}

static int led_init(void) {

    LOG_INF(">>> led_init ENTER <<<");

    int ret;

    if (!device_is_ready(led_gpio1.port) || !device_is_ready(led_gpio2.port)) {
        LOG_ERR("LED GPIO device NOT ready");
        return -ENODEV;
    }

    LOG_INF("LED GPIO device ready");

    // ret = gpio_pin_configure_dt(&led_gpio, GPIO_OUTPUT_INACTIVE); //led0 has been configured as
    // NUMLOCK INDICATOR in pad17air.overlay
    ret = gpio_pin_configure_dt(&led_gpio1, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        return ret;
    }
    LOG_INF("led_gpio1 configure ret=%d", ret);

    ret = gpio_pin_configure_dt(&led_gpio2, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        return ret;
    }

    k_timer_init(&led_timer, led_timer_handler, NULL);
    LOG_INF(">>> led_init() DONE <<<");

    return 0;
}

SYS_INIT(led_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
// #endif

void led_set_blink_fast(void) {

    // #ifdef QF_BLINK_LED

    LOG_INF("11 led set blak fast....");

    blink_interval_ms = 100; // 快闪

    k_timer_stop(&led_timer);
    k_timer_start(&led_timer, K_MSEC(blink_interval_ms), K_MSEC(blink_interval_ms));
    // #endif
}

void led_set_blink_slow(void) {
    // #ifdef QF_BLINK_LED
    LOG_INF("2222 led_set_blink_slow....");

    blink_interval_ms = 500;
    blink_cnt = 0;
    k_timer_stop(&led_timer);
    k_timer_start(&led_timer, K_MSEC(blink_interval_ms), K_MSEC(blink_interval_ms));
    // #endif
}
