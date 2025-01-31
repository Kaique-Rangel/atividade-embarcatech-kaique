# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

# Project name and languages
project(LEDs_Matrix C CXX ASM)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Automatically gather all source files from src/
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.c)

# Add executable using the gathered source files and LEDs_Matrix.c
add_executable(LEDs_Matrix ${SRC_FILES} ${CMAKE_SOURCE_DIR}/LEDs_Matrix.c)

# Set program name and version
pico_set_program_name(LEDs_Matrix "LEDs_Matrix")
pico_set_program_version(LEDs_Matrix "0.1")

pico_generate_pio_header(LEDs_Matrix ${CMAKE_SOURCE_DIR}/src/PIO_matrix.pio)

# Modify the following lines to enable/disable output over UART/USB
pico_enable_stdio_uart(LEDs_Matrix 1)
pico_enable_stdio_usb(LEDs_Matrix 1)

# Add the standard library to the build
target_link_libraries(LEDs_Matrix pico_stdlib hardware_pio hardware_adc)

# Add the standard include files to the build
target_include_directories(LEDs_Matrix PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Add extra outputs like UF2 files
pico_add_extra_outputs(LEDs_Matrix)
