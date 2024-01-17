#pragma once

#include "../sdk-quickstart/SignalingManager.h"
#include "AuthenticationEventHandler.h"

class SignalingManagerAuthentication : public SignalingManager
{
public:
    SignalingManagerAuthentication();
    std::string fetchRTMToken(std::string userId);
    std::string fetchRTCToken(std::string channelName);
    virtual void loginWithToken(std::string userId);
    int renewToken();

private:
    std::string serverUrl;
    int tokenExpiryTime;
    std::string fetchToken(std::string userId);
};
