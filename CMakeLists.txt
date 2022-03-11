# 
# (C) aviware 2022
# Author: Arian Ghoddousi, BSc
# Contact: arian.ghoddousi@aviware.net 
# Project: joanneum Aeronautics | AIAA DBF 22 | Package Deployment
# Date: 18 Feb 2022
#

cmake_minimum_required(VERSION 3.16.3)

set(HAVE_FLAG_SEARCH_PATHS_FIRST 0)

project("JA DBF Deploy Control")

set(PRODUCT_NAME deploycontrol)

set(F_CPU 8000000UL)

set(MCU atmega8u2)

set(BAUD 9600)

set(PROG_TYPE usbasp)

set(E_FUSE 0xe2)
set(H_FUSE 0xd9)
set(L_FUSE 0xff)
set(LOCK_BIT 0xff)


# Use AVR GCC toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER /usr/local/bin/avr-g++)
set(CMAKE_C_COMPILER /usr/local/bin/avr-gcc)
set(CMAKE_ASM_COMPILER /usr/local/bin/avr-gcc)

add_definitions(
    -DF_CPU=${F_CPU}
    -DBAUD=${BAUD}
)

set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})

add_compile_options(
    -mmcu=${MCU}
    -std=c++14
    -Os
    -Wall
    -Wno-main
    -Wundef
    -pedantic
    -Werror
    -Wfatal-errors
    -Wl,--relax,--gc-sections
    -g
    -gdwarf-2
    -funsigned-char
    -funsigned-bitfields
    -fpack-struct
    -fshort-enums
    -ffunction-sections
    -fdata-sections
    -fno-split-wide-types
    -fno-tree-scev-cprop
)

set(SRC_FILES 
    src/brakes.cpp
    src/deploycore.cpp
    src/main.cpp
    src/motorcontroller.cpp
    src/servo.cpp
    src/statusleds.cpp
    src/steppermotor.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include/)

add_executable(${PRODUCT_NAME} ${SRC_FILES})

set_target_properties(${PRODUCT_NAME} PROPERTIES OUTPUT_NAME ${PRODUCT_NAME}.elf)

add_custom_target(strip ALL avr-strip ${PRODUCT_NAME}.elf DEPENDS ${PRODUCT_NAME})

add_custom_target(hex ALL avr-objcopy -R .eeprom -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.hex DEPENDS strip)

add_custom_target(eeprom avr-objcopy -j .eeprom  --set-section-flags=.eeprom="alloc,load"  --change-section-lma .eeprom=0 -O ihex ${PRODUCT_NAME}.elf ${PRODUCT_NAME}.eep DEPENDS strip)

add_custom_target(upload avrdude  -c ${PROG_TYPE} -p ${MCU} -U flash:w:${PRODUCT_NAME}.hex DEPENDS hex)

add_custom_target(upload_eeprom avrdude -c ${PROG_TYPE} -p ${MCU}  -U eeprom:w:${PRODUCT_NAME}.eep DEPENDS eeprom)

add_custom_target(fuses avrdude -c ${PROG_TYPE} -p ${MCU}  -U lfuse:w:${L_FUSE}:m -U hfuse:w:${H_FUSE}:m -U efuse:w:${E_FUSE}:m -U lock:w:${LOCK_BIT}:m )

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PRODUCT_NAME}.hex;${PRODUCT_NAME}.eeprom;${PRODUCT_NAME}.lst")