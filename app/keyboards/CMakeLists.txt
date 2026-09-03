cmake_minimum_required(VERSION 3.20)

#### Set a append variable
set_property(GLOBAL APPEND PROPERTY MXKBD_USER_SRC)
set_property(GLOBAL APPEND PROPERTY MXKBD_USER_INC)
set_property(GLOBAL PROPERTY MXKBD_USER_LINKER_SCRIPT)


function(mxkbd_include_cmake)
    foreach(arg ${ARGV})
        if(IS_ABSOLUTE ${arg})
            set(path ${arg})
        else()
            set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
        endif()

        include(${path})
    endforeach()
endfunction()

function(mxkbd_append_user_src)
    foreach(arg ${ARGV})
        if(IS_ABSOLUTE ${arg})
            set(path ${arg})
        else()
            set(path ${CMAKE_CURRENT_LIST_DIR}/${arg})
        endif()

        file(GLOB MXKBD_USER_SRC_LIST CMAKE_CONFIGURE_DEPENDS ${path})
        set_property(GLOBAL APPEND PROPERTY MXKBD_USER_SRC ${MXKBD_USER_SRC_LIST})
    endforeach()
endfunction()

function(mxkbd_append_user_inc)
    foreach(arg ${ARGV})
        if(IS_ABSOLUTE ${arg})
            set(path ${arg})
        else()
            set(path ${CMAKE_CURRENT_LIST_DIR}/${arg})
        endif()

        file(GLOB MXKBD_USER_INC_LIST CMAKE_CONFIGURE_DEPENDS ${path})
        set_property(GLOBAL APPEND PROPERTY MXKBD_USER_INC ${MXKBD_USER_INC_LIST})
    endforeach()
endfunction()

function(mxkbd_set_user_ld ld)
    if(IS_ABSOLUTE ${ld})
        set(path ${ld})
    else()
        set(path ${CMAKE_CURRENT_LIST_DIR}/${ld})
    endif()

    set_property(GLOBAL PROPERTY MXKBD_USER_LINKER_SCRIPT ${path})
endfunction()

#### Find keyboard path rules
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${KEYBOARD}/rules.cmake")
    include(${CMAKE_CURRENT_LIST_DIR}/${KEYBOARD}/rules.cmake)
else()
    message(FATAL_ERROR "${KEYBOARD} does not contain rules.cmake ")
endif()

#### Find keymap path rules
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${KEYBOARD}/keymap/${KEYMAP}/rules.cmake")
    file(GLOB_RECURSE USER_RULES ${CMAKE_CURRENT_LIST_DIR}/${KEYBOARD}/keymap/${KEYMAP}/*.cmake)
    mxkbd_include_cmake(${USER_RULES})
endif()

#### Generate info_config.h default_keyboard.c default_keyboard.h
### python mxkbd.py generate-config-h --quiet --keyboard pilot/n40/keymap/l2r --output build/pivot/n40/temp_info_config.h
### python mxkbd.py generate-keyboard-h --quiet --keyboard pilot/n40/keymap/l2r --include pilot/n40.h --output build/pilot/n40/temp_default_keyboard.h

execute_process(
    COMMAND
        python scripts/west_commands/mxkbd.py generate-config-h --quiet --keyboard ${KEYBOARD}/keymap/${KEYMAP} --output build/${KEYBOARD}/temp_info_config.h
    COMMAND
        python scripts/west_commands/mxkbd.py generate-keyboard-h --quiet --keyboard ${KEYBOARD}/keymap/${KEYMAP} --include ${KEYBOARD}/${KEYBOARD}.h --output build/${KEYBOARD}/temp_default_keyboard.h
)

message(STATUS "temp_info_config      = build/${KEYBOARD}/temp_info_config.h")

file(READ "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/temp_info_config.h" TEMP_CONFIG_CONTENT)
if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/info_config.h")
    file(RENAME "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/temp_info_config.h" "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/info_config.h")
else()
    file(READ "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/info_config.h" EXISTING_CONFIG_CONTENT)
    if(NOT TEMP_CONFIG_CONTENT STREQUAL EXISTING_CONFIG_CONTENT)
        file(RENAME "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/temp_info_config.h" "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/info_config.h")
    else()
        file(REMOVE "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/temp_info_config.h")
    endif()
endif()

file(READ "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/temp_default_keyboard.h" TEMP_DEFAULT_KBD_CONTENT)
if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/default_keyboard.h")
    file(RENAME "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/temp_default_keyboard.h" "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/default_keyboard.h")
else()
    file(READ "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/default_keyboard.h" EXISTING_DEFAULT_KBD_CONTENT)
    if(NOT TEMP_DEFAULT_KBD_CONTENT STREQUAL EXISTING_DEFAULT_KBD_CONTENT)
        file(RENAME "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/temp_default_keyboard.h" "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/default_keyboard.h")
    else()
        file(REMOVE "${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/temp_default_keyboard.h")
    endif()
endif()

execute_process(
    COMMAND
        python scripts/west_commands/mxkbd.py generate-keyboard-c --quiet --keyboard ${KEYBOARD}/keymap/${KEYMAP}  --output build/${KEYBOARD}/default_keyboard.c
    COMMAND
        python scripts/west_commands/mxkbd.py generate-version-h --quiet -o build/${KEYBOARD}/src/version.h
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/src)

#### Find keyboard config.h
if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${KEYBOARD}/keymap/${KEYMAP}/config.h")
    file(COPY ${CMAKE_CURRENT_LIST_DIR}/${KEYBOARD}/keymap/${KEYMAP}/config.h DESTINATION ${CMAKE_CURRENT_LIST_DIR}/../build)
    file(RENAME ${CMAKE_CURRENT_LIST_DIR}/../build/config.h ${CMAKE_CURRENT_LIST_DIR}/../build/qmk_config.h)
    set(CMAKE_C_FLAGS "-include ${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/info_config.h ${CMAKE_C_FLAGS}")
    set(CMAKE_C_FLAGS "-include ${CMAKE_CURRENT_LIST_DIR}/../build/qmk_config.h ${CMAKE_C_FLAGS}" )
else()
    message(FATAL_ERROR "${KEYBOARD} does not contain config.h ")
endif()

#### define QMK_KEYBOARD_H 
add_compile_definitions(QMK_KEYBOARD_H="${CMAKE_CURRENT_LIST_DIR}/../build/${KEYBOARD}/default_keyboard.h")

#### Include board.cmake
include(${CMAKE_CURRENT_LIST_DIR}/../boards_qmk/${BOARD_QMK}/board.cmake)

#### Enter csdk config
# find_package(csdk REQUIRED HINTS $ENV{CSDK_BASE})s

#### Add keyboard and keymap inc
csdk_add_include_directories(${KEYBOARD} ${KEYBOARD}/keymap/${KEYMAP})

message(STATUS "adding dir  = ${CMAKE_CURRENT_LIST_DIR}/../boards_qmk/${BOARD_QMK}")
#### Add board inc
csdk_add_include_directories(${CMAKE_CURRENT_LIST_DIR}/../boards_qmk/${BOARD_QMK})
message(STATUS "adding dir 222 = ${CMAKE_CURRENT_LIST_DIR}/../boards_qmk/${BOARD_QMK}")

# csdk_add_include_directories(pilot/cx)
#### Append board.c
mxkbd_append_user_src(${CMAKE_CURRENT_LIST_DIR}/../boards_qmk/${BOARD_QMK}/board.c)

#### Target sources private keymap
# target_sources(app PRIVATE ${CMAKE_CURRENT_LIST_DIR}/${KEYBOARD}/keymap/${KEYMAP}/keymap.c)

csdk_add_compile_definitions(-DKEYMAP_C="${CMAKE_CURRENT_LIST_DIR}/${KEYBOARD}/keymap/${KEYMAP}/keymap.c")

#### Get user src
get_property(MXKBD_USER_SRC GLOBAL PROPERTY MXKBD_USER_SRC)
get_property(MXKBD_USER_INC GLOBAL PROPERTY MXKBD_USER_INC)
message(STATUS "777777APPLICATION_SOURCE_DIR = ${APPLICATION_SOURCE_DIR}")
set(ZEPHYR_EXTRA_MODULES
    ${ZMK_EXTRA_MODULES}
    ${CMAKE_CURRENT_SOURCE_DIR}/module
    ${CMAKE_CURRENT_SOURCE_DIR}/keymap-module
)


###e Add a user lib
csdk_generate_library(mx_kbd_user)
target_link_libraries(mx_kbd_user PUBLIC zephyr_interface)
target_compile_options(mx_kbd_user PRIVATE
    -include ${APPLICATION_SOURCE_DIR}/keyboards/${KEYBOARD}/keymap/${KEYMAP}/config.h
)

message(STATUS "99999 contains: ${APPLICATION_SOURCE_DIR}/keyboards/${KEYBOARD}/keymap/${KEYMAP}/config.h")
# set(CMAKE_C_FLAGS "-include ${CMAKE_CURRENT_LIST_DIR}/${KEYBOARD}/keymap/${KEYMAP}/config.h")


# csdk_add_compile_options_private(-Wno-unused-parameter)
# csdk_add_compile_options_private(-Wno-jump-misses-init)
# csdk_add_compile_options_private(-Wno-cast-align)
# csdk_add_compile_options_private(-Wno-old-style-definition)
# csdk_add_compile_options_private(-Wno-format)
# csdk_add_compile_options_private(-Wno-undef)
# csdk_add_compile_options_private(-Wno-unused-function)
# csdk_add_compile_options(-Wno-old-style-declaration)

#### Target sources MXKBD_USER_SRC
target_sources(mx_kbd_user PRIVATE ${MXKBD_USER_SRC})

#### Target include
target_include_directories(mx_kbd_user PRIVATE  ${MXKBD_USER_INC})
target_include_directories(mx_kbd_user PRIVATE
    ${APPLICATION_SOURCE_DIR}/include
)

