#pragma once

#include "../authentication-workflow/SignalingManagerAuthentication.h"
#include "../authentication-workflow/AuthenticationEventHandler.h"

class SignalingManagerProxy : public SignalingManagerAuthentication
{
public:
    SignalingManagerProxy();
    void loginWithToken(std::string userId) override;

private:
};
