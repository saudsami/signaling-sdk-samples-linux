#include "EncryptionEventHandler.h"
#include "SignalingManagerEncryption.h"

EncryptionEventHandler::EncryptionEventHandler(SignalingManager *manager)
    : BaseSignalingEventHandler(manager)
{
    signalingManagerEncryption = static_cast<SignalingManagerEncryption *>(signalingManager);
}

