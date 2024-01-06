# CMakeLists.txt
cmake_minimum_required (VERSION 3.0)
project(RTMProject)

# Set the build type
set(CMAKE_BUILD_TYPE "Debug")

# Compiler flags
set(CMAKE_CXX_FLAGS "-fPIC -O2 -g -std=c++11 -msse2")

# Define your library target
set(SIGNALLING_MANAGER_LIB SignalingManager)
add_library(${SIGNALLING_MANAGER_LIB} STATIC SignalingManager.cpp MyRtmEventHandler.cpp)

# Include directory for library users
target_include_directories(${SIGNALLING_MANAGER_LIB} PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Link libraries (if needed)
target_link_libraries(${SIGNALLING_MANAGER_LIB} PUBLIC agora_rtm_sdk pthread nlohmann_json::nlohmann_json)

# Optionally, you can install the library
install(TARGETS ${SIGNALLING_MANAGER_LIB} DESTINATION lib)

# Define your target
set(TARGET_NAME SignalingDemo)
add_executable(${TARGET_NAME} SignalingDemo.cpp QuickstartUI.cpp BaseUI.cpp)

# Include and link directories
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)

# Link libraries
target_link_libraries(${TARGET_NAME} PRIVATE ${SIGNALLING_MANAGER_LIB})
target_link_libraries(${TARGET_NAME} PRIVATE agora_rtm_sdk pthread)

# Fetch nlohmann/json
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# Link nlohmann/json library
target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)
