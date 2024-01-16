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
    void getChannelMetadata(std::string channelName);
    void setChannelMetadata(std::string key, std::string value, int64_t revision, std::string lockName);
    void updateChannelMetadata(std::string key, std::string value, int64_t revision, std::string lockName);
    void removeChannelMetadata(std::string key);

    void getUserMetadata(std::string userId);
    void setUserMetadata(std::string key, std::string value, int64_t revision);
    void removeUserMetadata(std::string key);
    void subscribeUserMetadata(std::string userId);
    void unsubscribeUserMetadata(std::string userId);
private:
};
