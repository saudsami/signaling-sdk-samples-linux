#pragma once

#include "../authentication-workflow/SignalingManagerAuthentication.h"
#include "EncryptionEventHandler.h"

class SignalingManagerEncryption : public SignalingManagerAuthentication
{
public:
    SignalingManagerEncryption();
    void loginWithToken(std::string userId) override;

private:
};
