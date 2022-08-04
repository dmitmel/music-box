cmake_minimum_required(VERSION 2.8)

include(cpplint.cmake)

# add the AVR toolchain
set(CMAKE_TOOLCHAIN_FILE "generic-avr-gcc.cmake")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

# device dependent config
set(AVR_MCU atmega328p)      # controller
set(MCU_FREQ 16000000UL)     # clock frequency
set(AVR_PROGRAMMER arduino)
# find a USB port
foreach(USB_PORT /dev/cu.usbmodem1411 /dev/cu.usbmodem1421)
  if (EXISTS ${USB_PORT})
    set(AVR_PROGRAMMER_PORT ${USB_PORT})
    break()
  endif ()
endforeach()
# set(AVR_PROGRAMMER_BAUDRATE 19200)
set(PROGRAM_EEPROM False)
# type of your board, see https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/variants
set(Arduino_VARIANT standard)

project(music-box)

# find Arduino libraries
#find_package(Arduino REQUIRED COMPONENTS core_arduino)
#include_directories(${Arduino_INCLUDE_DIRS})

set(music-box_SRCS main.cpp ports.h bits.h timer.cpp scheduler.cpp player.cpp melody.h)
set(music-box_CPPLINT_LINE_LENGTH 120)
set(music-box_CPPLINT_FILTER -whitespace -legal/copyright)
avr_add_executable(music-box ${music-box_SRCS})
#target_link_libraries(music-box.elf core_arduino)
cpplint(music-box)
