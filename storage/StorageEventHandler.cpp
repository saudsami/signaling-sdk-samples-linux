#include "StorageEventHandler.h"
#include "SignalingManagerStorage.h"

StorageEventHandler::StorageEventHandler(SignalingManager *manager)
    : BaseSignalingEventHandler(manager)
{
    signalingManagerStorage = static_cast<SignalingManagerStorage *>(signalingManager);
}

void onLockEvent(const LockEvent &event) {
    cbPrint("Lock event ")
}