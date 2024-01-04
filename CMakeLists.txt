# CMakeLists.txt
cmake_minimum_required (VERSION 2.9)
project(RTMProject)

# Set the build type
set(CMAKE_BUILD_TYPE "Debug")

# Compiler flags
set(CMAKE_CXX_FLAGS "-fPIC -O2 -g -std=c++11 -msse2")

# Define your target
set(TARGET_NAME RTMQuickStart)
add_executable(${TARGET_NAME} RTMQuickStart.cpp)

# Include and link directories
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)

# Link libraries
target_link_libraries(${TARGET_NAME} PRIVATE agora_rtm_sdk pthread)

# Fetch nlohmann/json
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# Link nlohmann/json library
target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)