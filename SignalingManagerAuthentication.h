#pragma once

#include "SignalingManager.h"

class SignalingManagerAuthentication : public SignalingManager {
public:
    SignalingManagerAuthentication();
    std::string fetchToken(std::string userId);
    void loginWithToken(std::string userId);

private:
    std::string serverUrl;
    int tokenExpiryTime;
};
