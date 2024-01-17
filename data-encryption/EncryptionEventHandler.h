#pragma once

class SignalingManagerEncryption;

#include "../authentication-workflow/AuthenticationEventHandler.h"

class EncryptionEventHandler : public AuthenticationEventHandler
{
public:
    EncryptionEventHandler(SignalingManager *manager);
    // Override event handlers from the base class
   
private:
    SignalingManagerEncryption *signalingManagerEncryption;
};