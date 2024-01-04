cmake_minimum_required (VERSION 2.6)
project (gui_test)

# Set the name of the executable to be produced
set(EXECUTABLE_NAME gui_test)

add_definitions(-DGLFW_STATIC)

include_directories("../src" "../libs/bitMapPlusPlus/include")

# Include GUI dependencies
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/BitmapPlusPlus/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/stb)

# Specify the link directories
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/lib)
file(GLOB IMGUI_SOURCES "../libs/imgui/*.cpp")

find_package(OpenGL REQUIRED)

file(GLOB SOURCES ../src/*.cpp)

# Add all .cpp files under src/ directory and the main executable
add_executable(${EXECUTABLE_NAME} ${SOURCES} main.cpp ${IMGUI_SOURCES})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Link libraries
target_link_libraries(${EXECUTABLE_NAME} glfw OpenGL::GL ${CMAKE_DL_LIBS})

# Set the build type (optional, but useful)
set(CMAKE_BUILD_TYPE Release)
# target_compile_options(gui_test PRIVATE -Wall -Wextra -Wpedantic -Werror)
