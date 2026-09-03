
#include <stdint.h>

void keyboard_pre_init_kb(void) {}

void keyboard_post_init_kb(void) {}
extern void battert_timer_start(void);
void main_post_init_qf(void) {}
// #include "rgb_matrix_types.h"
void housekeeping_task_user(void) {}

void bootmagic_lite(void) { /* Do nothing */
}
void bootmagic_scan(void) {}