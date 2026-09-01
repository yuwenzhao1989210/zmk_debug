#!/bin/bash
export PATH="/c/Users/dellht/AppData/Local/Programs/Python/Python314/Scripts:$PATH"
export PATH="/c/Users/dellht/AppData/Local/Programs/Python/Python314:$PATH"
export ZEPHYR_SDK_INSTALL_DIR="D:/zephyr-sdk-0.16.9"

# Make clean
export ORIG_CWD=$(pwd)
. ./common.sh

DRIVE_P=E

curr_folder=$(pwd)
echo "curr_folder_${curr_folder}"
clear

cd app || exit 1
  rm -rf build
  # -S nrf52833-nosd 
    SHIELD_TARGET="corne_right" 
    FILE_SUFFIX="_corne_right"
pwd
echo "Building for: $SHIELD_TARGET "


  # -S zmk-usb-logging \
  #-DCONFIG_ZMK_BLE=n 进制蓝牙方便开发速度
west build -b nice_nano_k \
   -S zmk-usb-logging \
   -- -DSHIELD=corne_right -DCONFIG_ZMK_BLE=y \
  -DKEYBOARD=pilot/npad -DKEYMAP=corne_v2
  



