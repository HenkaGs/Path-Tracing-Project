cmake_minimum_required(VERSION 3.10)
project(PathTracer)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the directory where stb_image.h is located to your include directories
include_directories(${CMAKE_SOURCE_DIR}/libs/stb)
include_directories(${CMAKE_SOURCE_DIR}/src)
# Gather all source files from the src directory
file(GLOB_RECURSE SOURCE_FILES 
     "${CMAKE_SOURCE_DIR}/src/*.cpp"
     "${CMAKE_SOURCE_DIR}/src/*.h")

# Specify the executable to be built from the source files
add_executable(PathTracer ${SOURCE_FILES})
                            
# If you're using any libraries that need to be linked, do so here
# target_link_libraries(${PROJECT_NAME} ...)

# If the libraries in libs/ have CMakeLists.txt files of their own,
# you might need to add them with add_subdirectory()
# add_subdirectory(${CMAKE_SOURCE_DIR}/libs/some_library)

# If you have any compiler flags to add
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g")

