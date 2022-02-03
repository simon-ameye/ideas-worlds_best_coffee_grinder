# Install script for directory: /Users/speedhacker/pico/libs/pimoroni-pico/drivers

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
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/analog/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/esp32spi/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/ioexpander/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/ltp305/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/ltr559/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/pmw3901/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sgp30/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/st7735/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/st7789/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/msa301/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/rv3028/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/trackball/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/vl53l1x/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/is31fl3731/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/fatfs/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/sdcard/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/as7262/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/bh1745/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/bme68x/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/bmp280/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/bme280/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/button/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/plasma/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/rgbled/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/icp10125/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/scd4x/cmake_install.cmake")
  include("/Users/speedhacker/pico/devs/first/build/pimoroni-drivers/hub75/cmake_install.cmake")

endif()

