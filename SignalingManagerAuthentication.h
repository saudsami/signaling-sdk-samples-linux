#pragma once

#include "SignalingManager.h"
#include "AuthenticationEventHandler.h"

class SignalingManagerAuthentication : public SignalingManager {
public:
    SignalingManagerAuthentication();
    std::string fetchToken(std::string userId);
    void loginWithToken(std::string userId);
    int renewToken();

private:
    std::string serverUrl;
    int tokenExpiryTime;
};
