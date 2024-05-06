cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(py_serial_tester)

pico_sdk_init()

add_executable(py_serial_tester
    hello_uart.c
)

target_link_libraries(py_serial_tester pico_stdlib hardware_uart)

pico_add_extra_outputs(py_serial_tester)
