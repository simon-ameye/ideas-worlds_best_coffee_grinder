# Install script for directory: /Users/speedhacker/pico/libs/pimoroni-pico/libraries

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/opt/homebrew/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_dotmatrix/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_encoder/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_ioexpander/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_ltr559/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_colourlcd160x80/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_colourlcd240x240/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_roundlcd/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_rgbmatrix5x5/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_matrix11x7/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_mics6814/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_paa5100/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_pmw3901/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_potentiometer/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_rtc/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_trackball/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_sgp30/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_as7262/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_msa301/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/breakout_bh1745/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/pico_graphics/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/pico_display/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/pico_display_2/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/pico_unicorn/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/pico_scroll/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/pico_explorer/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/pico_rgb_keypad/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/pico_wireless/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-libraries/plasma2040/cmake_install.cmake")

endif()

