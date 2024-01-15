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

class BaseSignalingEventHandler : public IRtmEventHandler
{
public:
  BaseSignalingEventHandler(SignalingManager *manager);
  // Add the event listener
  void onMessageEvent(const MessageEvent& event) override;
  void onPresenceEvent(const PresenceEvent& event) override;
  void onLoginResult(RTM_ERROR_CODE errorCode) override;
  void onConnectionStateChanged(const char *channelName, RTM_CONNECTION_STATE state, RTM_CONNECTION_CHANGE_REASON reason) override;
  void onPublishResult(const uint64_t requestId, RTM_ERROR_CODE errorCode) override;
  void onSubscribeResult(const uint64_t requestId, const char *channelName, RTM_ERROR_CODE errorCode) override;

protected:
  void cbPrint(const char *fmt, ...);
  SignalingManager *signalingManager;
};