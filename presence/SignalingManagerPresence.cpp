#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SignalingManagerPresence.h"


SignalingManagerPresence::SignalingManagerPresence()
    : SignalingManagerAuthentication() {
    // Additional initialization 
    
}

void SignalingManagerPresence::getOnlineUsers(std::string channelName) {
    GetOnlineUsersOptions options;
    options.includeState = true;
    options.includeUserId =true;
    int req_id = 99;

    int ret = signalingEngine->getPresence()->getOnlineUsers(channelName.c_str(), RTM_CHANNEL_TYPE_MESSAGE, options, req_id);
    if (ret != RTM_ERROR_OK) {
        printf("getOnlineUsers failed error is %d reason is %s\n", ret, getErrorReason(ret));
    }
}
