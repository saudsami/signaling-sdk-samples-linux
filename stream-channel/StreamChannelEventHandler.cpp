#include "StreamChannelEventHandler.h"
#include "SignalingManagerStreamChannel.h"

StreamChannelEventHandler::StreamChannelEventHandler(SignalingManager *manager)
    : BaseSignalingEventHandler(manager)
{
    signalingManagerStreamChannel = static_cast<SignalingManagerStreamChannel *>(signalingManager);
}

void StreamChannelEventHandler::onJoinResult(const uint64_t requestId, const char *channelName, const char *userId, RTM_ERROR_CODE errorCode)
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("join rtm channel failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("join rtm channel %s success\n", channelName);
    }
}

void StreamChannelEventHandler::onLeaveResult(const uint64_t requestId, const char *channelName, const char *userId, RTM_ERROR_CODE errorCode)
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("leave rtm channel failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("leave rtm channel %s success\n", channelName);
    }
}

void StreamChannelEventHandler::onJoinTopicResult(const uint64_t requestId, const char *channelName, const char *userId, const char *topic, const char *meta, RTM_ERROR_CODE errorCode) {
    if (errorCode != RTM_ERROR_OK) {
      printf("JoinTopic failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
    } else {
      printf("JoinTopic success\n");
    }
  }

 void StreamChannelEventHandler::onSubscribeTopicResult(const uint64_t requestId, const char *channelName, const char *userId, const char *topic, UserList succeedUsers, UserList failedUsers, RTM_ERROR_CODE errorCode) {
    if (errorCode != RTM_ERROR_OK) {
      printf("SubscribeTopic failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
    } else {
      printf("SubscribeTopic success\n");
    }
  }

void StreamChannelEventHandler::onLeaveTopicResult(const uint64_t requestId, const char *channelName, const char *userId, const char *topic, const char *meta, RTM_ERROR_CODE errorCode) {
    if (errorCode != RTM_ERROR_OK) {
      printf("LeaveTopic failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
    } else {
      printf("LeaveTopic success\n");
    }
  }