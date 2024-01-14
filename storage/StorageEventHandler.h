#pragma once

class SignalingManagerStorage;

#include "../sdk-quickstart/BaseSignalingEventHandler.h"

class StorageEventHandler : public BaseSignalingEventHandler
{
public:
    StorageEventHandler(SignalingManager *manager);
    // Override event handlers from the base class
    // void onStorageRemoveStateResult(const uint64_t requestId, RTM_ERROR_CODE errorCode) override;

private:
    SignalingManagerStorage *signalingManagerStorage;
};