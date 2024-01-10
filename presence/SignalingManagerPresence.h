#pragma once

#include "../authentication-workflow/SignalingManagerAuthentication.h"
#include "PresenceEventHandler.h"

class SignalingManagerPresence : public SignalingManagerAuthentication {
public:
    SignalingManagerPresence();
    void getOnlineUsers(std::string);
private:

};
