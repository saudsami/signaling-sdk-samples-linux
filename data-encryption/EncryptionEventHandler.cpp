#include "EncryptionEventHandler.h"
#include "SignalingManagerEncryption.h"

EncryptionEventHandler::EncryptionEventHandler(SignalingManager *manager)
    : AuthenticationEventHandler(manager)
{
    signalingManagerEncryption = static_cast<SignalingManagerEncryption *>(signalingManager);
}

