#pragma once

class SignalingManagerAuthentication;

#include "../sdk-quickstart/BaseSignalingEventHandler.h"

class AuthenticationEventHandler : public BaseSignalingEventHandler
{
public:
    AuthenticationEventHandler(SignalingManager *manager);

    // Override the onTokenPrivilegeWillExpire method
    void onTokenPrivilegeWillExpire(const char *channelName) override;

private:
    SignalingManagerAuthentication *signalingManagerAuthentication;
};