#pragma once

#include "../authentication-workflow/SignalingManagerAuthentication.h"
#include "PresenceEventHandler.h"

class SignalingManagerPresence : public SignalingManagerAuthentication
{
public:
    SignalingManagerPresence();
    void getOnlineUsers(std::string channelName);
    void getUserChannels(std::string userId);
    void setState(std::string channelName, std::string key, std::string value);
    void getState(std::string channelName, std::string userId);
    void removeState(std::string channelName, std::string key);

private:
};
