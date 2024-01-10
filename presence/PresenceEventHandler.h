#pragma once

class SignalingManagerPresence; 

#include "../sdk-quickstart/BaseSignalingEventHandler.h"

class PresenceEventHandler : public BaseSignalingEventHandler {
public:
    PresenceEventHandler(SignalingManager* manager);
    // Override event handlers from the base class
    void onGetOnlineUsersResult(const uint64_t requestId, const UserState *userStateList, const size_t count, const char *nextPage, RTM_ERROR_CODE errorCode) override;
    void onGetUserChannelsResult(const uint64_t requestId, const ChannelInfo* channels, const size_t count, RTM_ERROR_CODE errorCode) override;
    void onPresenceGetStateResult(const uint64_t requestId, const UserState &state, RTM_ERROR_CODE errorCode) override;
    void onPresenceSetStateResult(const uint64_t requestId, RTM_ERROR_CODE errorCode) override;
    void onPresenceRemoveStateResult(const uint64_t requestId, RTM_ERROR_CODE errorCode) override;

private:
    SignalingManagerPresence* signalingManagerPresence;
};