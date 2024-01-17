#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SignalingManagerGeofencing.h"

SignalingManagerGeofencing::SignalingManagerGeofencing()
    : SignalingManagerAuthentication()
{
    // Additional initialization
    eventHandler_ = std::unique_ptr<AuthenticationEventHandler>(new AuthenticationEventHandler(this));
}

void SignalingManagerGeofencing::loginWithToken(std::string userId)
{
    std::cout << "Fetching token from the server..." << std::endl;
    token = fetchRTMToken(userId);
    uid = userId;

    RtmConfig rtmConfig;
    rtmConfig.appId = appId.c_str();
    rtmConfig.userId = uid.c_str();
    rtmConfig.presenceTimeout = config["presenceTimeout"];
    rtmConfig.eventHandler = eventHandler_.get();

    std::cout << "Setting area code\n";
    rtmConfig.areaCode = RTM_AREA_CODE_NA;

    // Initialize the signalingEngine
    int ret = signalingEngine->initialize(rtmConfig);
    std::cout << "Initialize returned: " << ret << std::endl;
    if (ret)
    {
        std::cout << "Error initializing Signaling service: " << ret << std::endl;
        exit(0);
    }

    // Log in using the token
    ret = signalingEngine->login(token.c_str());
    std::cout << "Login returned: " << ret << std::endl;
    if (ret)
    {
        std::cout << "Login failed: " << ret << std::endl;
        exit(0);
    }
}
