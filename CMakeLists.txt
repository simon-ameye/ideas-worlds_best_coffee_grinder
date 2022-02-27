cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
include(pimoroni_pico_import.cmake)

project(Grinder)

pico_sdk_init()

add_executable(
	Grinder
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
	Hx711.cpp
	Hx711.hpp
)

pico_add_extra_outputs(Grinder)

#target_link_libraries(explorer pico_stdlib pico_explorer msa301)
target_link_libraries(Grinder pico_stdlib pico_explorer hardware_pio)

add_subdirectory(/Users/speedhacker/pico/libs/pimoroni-pico/common pimoroni-common)
add_subdirectory(/Users/speedhacker/pico/libs/pimoroni-pico/drivers pimoroni-drivers)
add_subdirectory(/Users/speedhacker/pico/libs/pimoroni-pico/libraries pimoroni-libraries)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)