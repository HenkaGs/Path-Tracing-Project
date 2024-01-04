cmake_minimum_required (VERSION 2.6)
project (gui_test)

# Set the name of the executable to be produced
set(EXECUTABLE_NAME gui_test)

add_definitions(-DGLFW_STATIC)

include_directories("../src")

# Include GUI dependencies
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/BitmapPlusPlus/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/stb)

# Specify the link directories
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/lib)
file(GLOB IMGUI_SOURCES "../libs/imgui/*.cpp")

file(GLOB SOURCES ../src/*.cpp)

# Add all .cpp files under src/ directory and the main executable
add_executable(${EXECUTABLE_NAME} ${SOURCES} main.cpp ${IMGUI_SOURCES})


# Link libraries
target_link_libraries(${EXECUTABLE_NAME} glfw3 opengl32)

# Set the build type (optional, but useful)
set(CMAKE_BUILD_TYPE Release)