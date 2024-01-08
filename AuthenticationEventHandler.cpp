#include "AuthenticationEventHandler.h"
#include "SignalingManagerAuthentication.h"

AuthenticationEventHandler::AuthenticationEventHandler(SignalingManager* manager)
    : MyRtmEventHandler(manager) {
        signalingManagerAuthentication = static_cast<SignalingManagerAuthentication*>(signalingManager);
}

void AuthenticationEventHandler::onTokenPrivilegeWillExpire(const char* channelName) {
    signalingManagerAuthentication->renewToken();
}