#cmake .. && make && cp pico_test.uf2 /Volumes/RPI-RP2 && minicom -o -D /dev/cu.usbmodem1101

cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
include(pimoroni_pico_import.cmake)

project(pico_test)

pico_sdk_init()

add_executable(
	pico_test
	main.cpp
	serial_print.cpp
	serial_print.hpp
	Stepper.cpp
	Stepper.hpp
	UserInterface.hpp
	Userinterface.cpp
	Grinder.cpp
	Grinder.hpp
	Balance.cpp
	Balance.hpp
)

pico_add_extra_outputs(pico_test)

# Create C header file with the name <pio program>.pio.h
pico_generate_pio_header(${PROJECT_NAME}  
        ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

#target_link_libraries(explorer pico_stdlib pico_explorer msa301)
target_link_libraries(pico_test pico_stdlib pico_explorer hardware_pio)

add_subdirectory(/Users/speedhacker/pico/libs/pimoroni-pico/common pimoroni-common)
add_subdirectory(/Users/speedhacker/pico/libs/pimoroni-pico/drivers pimoroni-drivers)
add_subdirectory(/Users/speedhacker/pico/libs/pimoroni-pico/libraries pimoroni-libraries)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)