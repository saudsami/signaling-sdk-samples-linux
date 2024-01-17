#pragma once

#include "../authentication-workflow/SignalingManagerAuthentication.h"
#include "../authentication-workflow/AuthenticationEventHandler.h"

class SignalingManagerGeofencing : public SignalingManagerAuthentication
{
public:
    SignalingManagerGeofencing();
    void loginWithToken(std::string userId) override;

private:
};
