#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SignalingManagerPresence.h"

SignalingManagerPresence::SignalingManagerPresence()
    : SignalingManagerAuthentication()
{
    // Additional initialization
    eventHandler_ = std::unique_ptr<PresenceEventHandler>(new PresenceEventHandler(this));
}

void SignalingManagerPresence::getOnlineUsers(std::string channelName)
{
    GetOnlineUsersOptions options;
    options.includeState = true;  // Include user IDs of the online users
    options.includeUserId = true; // Include temporary status data of online users
    uint64_t requestId;           // Output parameter used to identify and process the result

    int ret = signalingEngine->getPresence()->getOnlineUsers(channelName.c_str(), RTM_CHANNEL_TYPE_MESSAGE, options, requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("getOnlineUsers failed error is %d reason is %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerPresence::getUserChannels(std::string userId)
{
    uint64_t requestId; // Output parameter used to identify and process the result

    int ret = signalingEngine->getPresence()->getUserChannels(userId.c_str(), requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("getUserChannels failed error is %d reason is %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerPresence::setState(std::string channelName, std::string key, std::string value)
{
    StateItem states[1];
    states[0] = StateItem();
    states[0].key = key.c_str();
    states[0].value = value.c_str();
    uint64_t requestId; // Output parameter used to identify and process the result

    int ret = signalingEngine->getPresence()->setState(channelName.c_str(), RTM_CHANNEL_TYPE_MESSAGE, states, 1, requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("setState failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerPresence::getState(std::string channelName, std::string userId)
{
    uint64_t requestId; // Output parameter used to identify and process the result

    int ret = signalingEngine->getPresence()->getState(channelName.c_str(), RTM_CHANNEL_TYPE_MESSAGE, userId.c_str(), requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("getState failed error is %d reason is %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerPresence::removeState(std::string channelName, std::string key)
{
    const char *keys[1] = {key.c_str()}; // List of keys that need to be deleted key.
    uint64_t requestId;                  // Output parameter used to identify and process the result

    int ret = signalingEngine->getPresence()->removeState(channelName.c_str(), RTM_CHANNEL_TYPE_MESSAGE, keys, 1, requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("removeState failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}
