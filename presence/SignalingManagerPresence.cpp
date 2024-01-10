#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SignalingManagerPresence.h"


SignalingManagerPresence::SignalingManagerPresence()
    : SignalingManagerAuthentication() {
    // Additional initialization 
    eventHandler_ = std::unique_ptr<PresenceEventHandler>(new PresenceEventHandler(this));
}

void SignalingManagerPresence::getOnlineUsers(std::string channelName) {
    GetOnlineUsersOptions options;
    options.includeState = true; // Include user IDs of the online users
    options.includeUserId =true; // Include temporary status data of online users
    uint64_t requestId; // Output parameter used to identify and process the result

    int ret = signalingEngine->getPresence()->getOnlineUsers(channelName.c_str(), RTM_CHANNEL_TYPE_MESSAGE, options, requestId);
    if (ret != RTM_ERROR_OK) {
        printf("getOnlineUsers failed error is %d reason is %s\n", ret, getErrorReason(ret));
    }
}

int SignalingManagerPresence::getUserChannels(const char* userId, uint64_t& requestId) {
    uint64_t requestId; // Output parameter used to identify and process the result
    
    int ret = signalingEngine->getPresence()->getUserChannels(userId, requestId);
    if (ret != RTM_ERROR_OK) {
        printf("getUserChannels failed error is %d reason is %s\n", ret, getErrorReason(ret));
    }
}