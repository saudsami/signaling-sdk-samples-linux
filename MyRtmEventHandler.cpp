#include "IAgoraRtmClient.h"
#include "MyRtmEventHandler.h"
#include "SignalingManager.h"

using namespace agora::rtm;
using json = nlohmann::json;

MyRtmEventHandler::MyRtmEventHandler(SignalingManager* manager)
    : signalingManager(manager) {
}

void MyRtmEventHandler::onLoginResult(RTM_ERROR_CODE errorCode) {
    cbPrint("onLogin: errorCode: %d", errorCode);
}

void MyRtmEventHandler::onConnectionStateChanged(const char *channelName, RTM_CONNECTION_STATE state, RTM_CONNECTION_CHANGE_REASON reason) {
    cbPrint("onConnectionStateChanged: %d", state);
    bool isLoggedIn = (state == RTM_CONNECTION_STATE_CONNECTED);
    signalingManager->updateLoginStatus(isLoggedIn);
}

void MyRtmEventHandler::onPublishResult(const uint64_t requestId, RTM_ERROR_CODE errorCode) {
    cbPrint("onPublishResult request id: %llu result: %d", requestId, errorCode);
}

void MyRtmEventHandler::onMessageEvent(const MessageEvent &event) {
    cbPrint("received message from: %s, message: %s", event.publisher, event.message);
}

void MyRtmEventHandler::onSubscribeResult(const uint64_t requestId, const char *channelName, RTM_ERROR_CODE errorCode) {
    cbPrint("onSubscribeResult: channel:%s, request id: %llu result: %d", channelName, requestId, errorCode);
}

void MyRtmEventHandler::cbPrint(const char* fmt, ...) {
    printf("\x1b[32m<< RTM async callback: ");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf(" >>\x1b[0m\n");
}