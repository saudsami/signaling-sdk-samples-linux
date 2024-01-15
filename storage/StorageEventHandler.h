#pragma once

class SignalingManagerStorage;

#include "../sdk-quickstart/BaseSignalingEventHandler.h"

class StorageEventHandler : public BaseSignalingEventHandler
{
public:
    StorageEventHandler(SignalingManager *manager);
    // Override event handlers from the base class
    void onLockEvent(const LockEvent &event) override;

private:
    SignalingManagerStorage *signalingManagerStorage;
};