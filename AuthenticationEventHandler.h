#pragma once

class SignalingManagerAuthentication; 

#include "MyRtmEventHandler.h"

class AuthenticationEventHandler : public MyRtmEventHandler {
public:
    AuthenticationEventHandler(SignalingManager* manager);

    // Override the onTokenPrivilegeWillExpire method
    void onTokenPrivilegeWillExpire(const char* channelName) override;

private:
    SignalingManagerAuthentication* signalingManagerAuthentication;
};