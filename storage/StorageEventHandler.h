#pragma once

class SignalingManagerStorage;

#include "../sdk-quickstart/BaseSignalingEventHandler.h"

class StorageEventHandler : public BaseSignalingEventHandler
{
public:
    StorageEventHandler(SignalingManager *manager);
    // Override event handlers from the base class
    void onLockEvent(const LockEvent &event) override;
    void onSetLockResult(const uint64_t requestId,
                         const char *channelName, RTM_CHANNEL_TYPE channelType, const char *lockName,
                         RTM_ERROR_CODE errorCode) override;
    void onAcquireLockResult(const uint64_t requestId, const char *channelName, RTM_CHANNEL_TYPE channelType, const char *lockName, RTM_ERROR_CODE errorCode, const char *errorDetails) override;
    void onReleaseLockResult(const uint64_t requestId, const char *channelName, RTM_CHANNEL_TYPE channelType, const char *lockName, RTM_ERROR_CODE errorCode) override;
    void onRemoveLockResult(const uint64_t requestId, const char *channelName, RTM_CHANNEL_TYPE channelType, const char *lockName, RTM_ERROR_CODE errorCode) override;
    void onGetLocksResult(const uint64_t requestId, const char *channelName, RTM_CHANNEL_TYPE channelType, const LockDetail *lockDetailList, const size_t count, RTM_ERROR_CODE errorCode) override;
private:
    SignalingManagerStorage *signalingManagerStorage;
    std::string getLockEventDescription(RTM_LOCK_EVENT_TYPE eventType);
};