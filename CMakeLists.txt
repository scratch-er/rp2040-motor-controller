# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(motor-controller C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(motor-controller motor-controller.c )

pico_set_program_name(motor-controller "motor-controller")
pico_set_program_version(motor-controller "0.1")

pico_enable_stdio_uart(motor-controller 0)
pico_enable_stdio_usb(motor-controller 1)

# Add the standard library to the build
target_link_libraries(motor-controller pico_stdlib)

# Add any user requested libraries
target_link_libraries(motor-controller
        hardware_pio
        )

pico_add_extra_outputs(motor-controller)

