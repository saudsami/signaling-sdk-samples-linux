# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(RTMProject)

# Set the build type
set(CMAKE_BUILD_TYPE "Debug")

# Compiler flags
set(CMAKE_CXX_FLAGS "-fPIC -O2 -g -std=c++11 -msse2")

# Define your library target
set(SIGNALLING_MANAGER_LIB SignalingManager)
add_library(${SIGNALLING_MANAGER_LIB} STATIC
    sdk-quickstart/SignalingManager.cpp
    sdk-quickstart/BaseSignalingEventHandler.cpp
    authentication-workflow/SignalingManagerAuthentication.cpp
    authentication-workflow/AuthenticationEventHandler.cpp
    presence/SignalingManagerPresence.cpp
    presence/PresenceEventHandler.cpp
    stream-channel/SignalingManagerStreamChannel.cpp
    stream-channel/StreamChannelEventHandler.cpp
    storage/SignalingManagerStorage.cpp
    storage/StorageEventHandler.cpp
    data-encryption/SignalingManagerEncryption.cpp
    geofencing/SignalingManagerGeofencing.cpp
    proxy-service/SignalingManagerProxy.cpp
)

# Include directory for library users
target_include_directories(${SIGNALLING_MANAGER_LIB} PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Link libraries (if needed)
target_link_libraries(${SIGNALLING_MANAGER_LIB} PUBLIC agora_rtm_sdk pthread nlohmann_json::nlohmann_json)

# Add libcurl
find_package(CURL REQUIRED)
target_include_directories(${SIGNALLING_MANAGER_LIB} PUBLIC 
    ${CURL_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/sdk-quickstart 
    ${CMAKE_SOURCE_DIR}/authentication-workflow
    ${CMAKE_SOURCE_DIR}/presence
    ${CMAKE_SOURCE_DIR}/stream-channel
    ${CMAKE_SOURCE_DIR}/storage
    ${CMAKE_SOURCE_DIR}/data-encryption
    ${CMAKE_SOURCE_DIR}/geofencing
    ${CMAKE_SOURCE_DIR}/proxy-service
)
target_link_libraries(${SIGNALLING_MANAGER_LIB} PUBLIC ${CURL_LIBRARIES})

# Optionally, you can install the library
install(TARGETS ${SIGNALLING_MANAGER_LIB} DESTINATION lib)

# Define your target
set(TARGET_NAME SignalingDemo)
add_executable(${TARGET_NAME} 
    SignalingDemo.cpp 
    BaseUI.cpp 
    sdk-quickstart/QuickstartUI.cpp 
    authentication-workflow/AuthenticationWorkflowUI.cpp
    presence/PresenceUI.cpp
    stream-channel/StreamChannelUI.cpp
    storage/StorageUI.cpp
    data-encryption/EncryptionUI.cpp
    geofencing/GeofencingUI.cpp
    proxy-service/ProxyUI.cpp
)

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
