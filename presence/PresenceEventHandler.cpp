#include "PresenceEventHandler.h"
#include "SignalingManagerPresence.h"

PresenceEventHandler::PresenceEventHandler(SignalingManager* manager)
    : BaseSignalingEventHandler(manager) {
        signalingManagerPresence = static_cast<SignalingManagerPresence*>(signalingManager);
}

void PresenceEventHandler::onTokenPrivilegeWillExpire(const char* channelName) {
    int ret = signalingManagerPresence->renewToken();
    if (ret == 0) {
        std::cout << "Token renewed\n";
    }
}