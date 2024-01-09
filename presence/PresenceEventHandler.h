#pragma once

class SignalingManagerPresence; 

#include "../sdk-quickstart/BaseSignalingEventHandler.h"

class PresenceEventHandler : public BaseSignalingEventHandler {
public:
    PresenceEventHandler(SignalingManager* manager);

    // Override the onTokenPrivilegeWillExpire method
    void onTokenPrivilegeWillExpire(const char* channelName) override;

private:
    SignalingManagerPresence* signalingManagerPresence;
};