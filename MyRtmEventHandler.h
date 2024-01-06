#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <fstream>
#include <nlohmann/json.hpp>
#include "IAgoraRtmClient.h"
#include "SignalingManager.h"

using namespace agora::rtm;
using json = nlohmann::json;

class MyRtmEventHandler : public IRtmEventHandler {
  public:
    MyRtmEventHandler(SignalingManager* manager);
    // Add the event listener
    void onLoginResult(RTM_ERROR_CODE errorCode) override;
    void onConnectionStateChanged(const char *channelName, RTM_CONNECTION_STATE state, RTM_CONNECTION_CHANGE_REASON reason) override;
    void onPublishResult(const uint64_t requestId, RTM_ERROR_CODE errorCode) override;
    void onMessageEvent(const MessageEvent &event) override;
    void onSubscribeResult(const uint64_t requestId, const char *channelName, RTM_ERROR_CODE errorCode) override;

  private:
    // Add a pointer to SignalingManager
    SignalingManager* signalingManager; 
    void cbPrint(const char* fmt, ...);
};