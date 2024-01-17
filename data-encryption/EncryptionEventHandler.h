#pragma once

class SignalingManagerEncryption;

#include "../sdk-quickstart/BaseSignalingEventHandler.h"

class EncryptionEventHandler : public BaseSignalingEventHandler
{
public:
    EncryptionEventHandler(SignalingManager *manager);
    // Override event handlers from the base class
   
private:
    SignalingManagerEncryption *signalingManagerEncryption;
};