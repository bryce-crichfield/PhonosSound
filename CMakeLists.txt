# Minimum required CMake version
cmake_minimum_required(VERSION 3.12)

# Project name
project(PhonosSound)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE SOURCES Source/*.cpp)

# Add test files
file(GLOB_RECURSE TESTS Test/*.cpp)

# Create static library of source files
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Add include directories
target_include_directories(${PROJECT_NAME} PUBLIC Include)

# For each test, link the library and add an executable
# foreach(TEST ${TESTS})
#     get_filename_component(TEST_NAME ${TEST} NAME_WE)
#     add_executable(${TEST_NAME}.exe ${TEST})
#     target_link_libraries(${TEST_NAME}.exe ${PROJECT_NAME})
#     # target_include_directories(${TEST_NAME}.exe PUBLIC Include)
# endforeach()