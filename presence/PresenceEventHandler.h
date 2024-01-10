#pragma once

class SignalingManagerPresence; 

#include "../sdk-quickstart/BaseSignalingEventHandler.h"

class PresenceEventHandler : public BaseSignalingEventHandler {
public:
    PresenceEventHandler(SignalingManager* manager);

    // Override event handlers from the base class
    void onGetOnlineUsersResult(const uint64_t requestId, const UserState *userStateList, const size_t count, const char *nextPage, RTM_ERROR_CODE errorCode) override;
    int onGetUserChannelsResult(const char* userId, uint64_t& requestId) override;

private:
    SignalingManagerPresence* signalingManagerPresence;
};