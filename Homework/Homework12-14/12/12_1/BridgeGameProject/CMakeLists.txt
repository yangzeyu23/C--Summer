cmake_minimum_required(VERSION 3.10)

# Set the project name
project(BridgeGameProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files
include_directories(src)
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(BridgeGame ${SOURCES})