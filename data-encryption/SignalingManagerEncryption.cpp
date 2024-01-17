#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SignalingManagerEncryption.h"

SignalingManagerEncryption::SignalingManagerEncryption()
    : SignalingManagerAuthentication()
{
    // Additional initialization
    eventHandler_ = std::unique_ptr<AuthenticationEventHandler>(new AuthenticationEventHandler(this));
}

void SignalingManagerEncryption::loginWithToken(std::string userId)
{
    std::cout << "Fetching token from the server..." << std::endl;
    token = fetchRTMToken(userId);
    uid = userId;

    RtmConfig rtmConfig;
    rtmConfig.appId = appId.c_str();
    rtmConfig.userId = uid.c_str();
    rtmConfig.presenceTimeout = config["presenceTimeout"];
    rtmConfig.eventHandler = eventHandler_.get();

    std::cout << "Enabling data encryption\n";
    uint8_t salt[32] = {1,2,3,4,5,6,7,8};
    rtmConfig.encryptionConfig.encryptionKey = "your_encryption_key";
    rtmConfig.encryptionConfig.encryptionMode = RTM_ENCRYPTION_MODE_AES_256_GCM;
    memcpy(rtmConfig.encryptionConfig.encryptionSalt, salt, 32);

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
