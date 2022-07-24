cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(pico_sdk_import.cmake)
project(motor-controller C CXX ASM)
pico_sdk_init()

add_executable(motor-controller motor-controller.c )
pico_generate_pio_header(motor-controller ${CMAKE_CURRENT_LIST_DIR}/speedmeter.pio)

pico_set_program_name(motor-controller "motor-controller")
pico_set_program_version(motor-controller "0.1")

pico_enable_stdio_uart(motor-controller 1)
pico_enable_stdio_usb(motor-controller 1)

target_link_libraries(motor-controller pico_stdlib hardware_pio hardware_dma)

pico_add_extra_outputs(motor-controller)

