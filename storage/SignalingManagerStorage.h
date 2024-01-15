#pragma once

#include "../authentication-workflow/SignalingManagerAuthentication.h"
#include "StorageEventHandler.h"

class SignalingManagerStorage : public SignalingManagerAuthentication
{
public:
    SignalingManagerStorage();
    void setLock(std::string lockName);
    void acquireLock(std::string lockName);
    void releaseLock(std::string lockName);
    void removeLock(std::string lockName);
    void getLocks(std::string channelName);
private:
};
