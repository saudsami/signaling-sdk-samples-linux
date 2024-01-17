#pragma once

#include "../authentication-workflow/SignalingManagerAuthentication.h"
#include "../authentication-workflow/AuthenticationEventHandler.h"

class SignalingManagerEncryption : public SignalingManagerAuthentication
{
public:
    SignalingManagerEncryption();
    void loginWithToken(std::string userId) override;

private:
};
