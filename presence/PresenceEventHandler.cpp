#include "PresenceEventHandler.h"
#include "SignalingManagerPresence.h"

PresenceEventHandler::PresenceEventHandler(SignalingManager* manager)
    : BaseSignalingEventHandler(manager) {
        signalingManagerPresence = static_cast<SignalingManagerPresence*>(signalingManager);
}

void PresenceEventHandler::onGetOnlineUsersResult(const uint64_t requestId, 
    const UserState *userStateList, const size_t count, 
    const char *nextPage, RTM_ERROR_CODE errorCode) {
    
    if (errorCode != RTM_ERROR_OK) {
      printf("getOnlineUsers failed error is %d reason is %s\n", errorCode, getErrorReason(errorCode));
    } else {
      printf("getOnlineUsers success\n");
      for (int i = 0 ;i < count; i++) {
        printf("user: %s\n", userStateList[i].userId);
        for (int j = 0 ; j < userStateList[i].statesCount; j++) {
            printf("key: %s value: %s\n", userStateList[i].states[j].key, userStateList[i].states[j].value);
        }
      }
    }
}

int PresenceEventHandler::onGetUserChannelsResult(const uint64_t requestId, const ChannelInfo *channels, const size_t count, RTM_ERROR_CODE errorCode) {
    if (errorCode != RTM_ERROR_OK) {
      printf("getUserChannels failed error is %d reason is %s\n", errorCode, getErrorReason(errorCode));
    } else {
      printf("getUserChannels success\n");
      for (int i = 0; i < count; i++) {
        printf("channel: %s channel type: %d\n", channels[i].channelName, channels[i].channelType);
      }
    }
  }