#include "AuthenticationEventHandler.h"
#include "SignalingManagerAuthentication.h"

AuthenticationEventHandler::AuthenticationEventHandler(SignalingManager *manager)
    : BaseSignalingEventHandler(manager)
{
    signalingManagerAuthentication = static_cast<SignalingManagerAuthentication *>(signalingManager);
}

void AuthenticationEventHandler::onTokenPrivilegeWillExpire(const char *channelName)
{
    int ret = signalingManagerAuthentication->renewToken();
    if (ret == 0)
    {
        std::cout << "Token renewed\n";
    }
}