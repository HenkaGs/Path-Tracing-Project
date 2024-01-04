cmake_minimum_required (VERSION 2.6)
project (test)
include_directories("../../src")
# Set the name of the executable to be produced
set(EXECUTABLE_NAME test)

# Add all .cpp - files under src/ directory
file(GLOB SOURCES ../../src/*.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCES} main.cpp)
set(CMAKE_BUILD_TYPE Debug)
target_compile_options(test PRIVATE -Wall -Wextra -Wpedantic -Werror)
