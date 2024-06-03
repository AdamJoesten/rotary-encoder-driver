# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.22.1)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(
    ky040-driver
    VERSION 0.1
    DESCRIPTION "KY-040 rotary encoder library for Raspberry Pi Pico and RP2040 devices"
    HOMEPAGE_URL "https://www.github.com/AdamJoesten/ky040-driver"
    LANGUAGES CXX C ASM
)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Tell CMake where to find the executable source file
add_library(${PROJECT_NAME} STATIC
    Encoder.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Create map/bin/hex/uf2 files
# pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)