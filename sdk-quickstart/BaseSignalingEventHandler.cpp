#include "IAgoraRtmClient.h"
#include "BaseSignalingEventHandler.h"
#include "SignalingManager.h"

using namespace agora::rtm;
using json = nlohmann::json;

BaseSignalingEventHandler::BaseSignalingEventHandler(SignalingManager *manager)
    : signalingManager(manager)
{
}

void BaseSignalingEventHandler::onLoginResult(RTM_ERROR_CODE errorCode)
{
    cbPrint("onLogin: errorCode: %d", errorCode);
}

void BaseSignalingEventHandler::onConnectionStateChanged(const char *channelName, RTM_CONNECTION_STATE state, RTM_CONNECTION_CHANGE_REASON reason)
{
    std::string description = SignalingManager::getConnectionStateDescription(state) + "\n";
    cbPrint(description.c_str());
    bool isLoggedIn = (state == RTM_CONNECTION_STATE_CONNECTED);
    signalingManager->updateLoginStatus(isLoggedIn);
}

void BaseSignalingEventHandler::onPublishResult(const uint64_t requestId, RTM_ERROR_CODE errorCode)
{
    cbPrint("onPublishResult request id: %llu result: %d", requestId, errorCode);
}

void BaseSignalingEventHandler::onMessageEvent(const MessageEvent &event)
{
    cbPrint("received message from: %s, message: %s", event.publisher, event.message);
}

void BaseSignalingEventHandler::onPresenceEvent(const PresenceEvent &event)
{
    if (event.type == RTM_PRESENCE_EVENT_TYPE_REMOTE_JOIN_CHANNEL)
    {
        cbPrint("presence: remote user joined, publisher: %d", event.type, event.publisher);
    }
    else if (event.type == RTM_PRESENCE_EVENT_TYPE_REMOTE_LEAVE_CHANNEL)
    {
        cbPrint("presence: remote user left, publisher: %d", event.type, event.publisher);
    }
    {
        cbPrint("presence event: %d, publisher: %s", event.type, event.publisher);
    }
}

void BaseSignalingEventHandler::onSubscribeResult(const uint64_t requestId, const char *channelName, RTM_ERROR_CODE errorCode)
{
    cbPrint("onSubscribeResult: channel:%s, request id: %llu result: %d", channelName, requestId, errorCode);
}

void BaseSignalingEventHandler::cbPrint(const char *fmt, ...)
{
    printf("\x1b[32m<< RTM async callback: ");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf(" >>\x1b[0m\n");
}