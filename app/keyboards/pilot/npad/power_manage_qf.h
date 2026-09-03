
#pragma once


#include "output_select.h"
#include "protocol_mode.h"
#include "qf.h"

// void keyboard_sleep_counter_reset(void);

/// power mgr provided 2 feature
/// auto sleep detection and battery detection
void power_mgr_init(void);

void power_mgr_start();

void sleep_mode_enter(void);
void sleep_mode_enterFS(void);
void sleep_mode_enter_special(void);
void keyboard_tick_handler_qf(void);

uint32_t getSWADC(void);
void rgb_power_enable(bool enable);
