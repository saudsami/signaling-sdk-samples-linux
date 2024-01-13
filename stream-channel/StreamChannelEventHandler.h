#pragma once

class SignalingManagerStreamChannel;

#include "../sdk-quickstart/BaseSignalingEventHandler.h"

class StreamChannelEventHandler : public BaseSignalingEventHandler
{
public:
    StreamChannelEventHandler(SignalingManager *manager);
    // Override event handlers from the base class
    void onJoinResult(const uint64_t requestId, const char *channelName, const char *userId, RTM_ERROR_CODE errorCode) override;
    void onLeaveResult(const uint64_t requestId, const char *channelName, const char *userId, RTM_ERROR_CODE errorCode) override;
    void onTopicEvent(const TopicEvent &event) override;
    void onJoinTopicResult(const uint64_t requestId, const char *channelName, const char *userId, const char *topic, const char *meta, RTM_ERROR_CODE errorCode) override;
    void onLeaveTopicResult(const uint64_t requestId, const char *channelName, const char *userId, const char *topic, const char *meta, RTM_ERROR_CODE errorCode) override;
    void onSubscribeTopicResult(const uint64_t requestId, const char *channelName, const char *userId, const char *topic, UserList succeedUsers, UserList failedUsers, RTM_ERROR_CODE errorCode) override;

private:
    SignalingManagerStreamChannel *signalingManagerStreamChannel;
};