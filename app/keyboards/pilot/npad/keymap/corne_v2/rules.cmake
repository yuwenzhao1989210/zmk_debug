set(BOARD_QMK "nrf52833_kit" CACHE STRING "KB" FORCE)
mxkbd_set_user_ld(Ld/nrf52833_esb.ld)
add_compile_definitions(QMK_MCU_NRF52833)

set(RGB_MATRIX_ENABLE ON CACHE BOOL "KB" FORCE)
set(RGB_MATRIX_DRIVER "ws2812" CACHE STRING "KB" FORCE)
set(WS2812_DRIVER "pwm" CACHE STRING "KB" FORCE)
# set(BLE_ENABLE ON CACHE BOOL "KB" FORCE)
set(UF2_FAMILY_ID "0x621e937a" CACHE STRING "KB" FORCE)
set(CUSTOM_MATRIX "lite" CACHE STRING "KB" FORCE)


mxkbd_append_user_src(../../../cross/protocol_esb_major.c)
mxkbd_append_user_src(../../../cross/protocol_esb_other.c)
mxkbd_append_user_src(../../../cross/protocol_qmk_qf.c)
mxkbd_append_user_src(../../../cross/usb_main_pad.c)
mxkbd_append_user_src(../../../cross/keymap_cb.c)
mxkbd_append_user_src(../../../cross/keys_hold.c)
mxkbd_append_user_src(../../../cross/ble_major.c)
mxkbd_append_user_src(../../../cross/qf_channel_manage.c)

mxkbd_append_user_src(../output_select.c)
mxkbd_append_user_src(../../common/power_m.c)
mxkbd_append_user_src(../../common/power_hibernate.c)
mxkbd_append_user_src(../../common/power_manage_qf.c)
mxkbd_append_user_src(../n40.c)

mxkbd_append_user_src(../eeprom_qf.c)
mxkbd_append_user_src(../matrix_qf.c)

mxkbd_append_user_src(../matrix_s.c)


