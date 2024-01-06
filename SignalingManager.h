#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <fstream>
#include <nlohmann/json.hpp>
#include "IAgoraRtmClient.h"

using namespace agora::rtm;
using json = nlohmann::json;

class SignalingManager {
  public:
    SignalingManager();
    void Init();
    void login();
    void logout();
    void subscribeChannel(std::string chnId);
    void unsubscribeChannel(std::string chnId);
    void publishMessage(std::string chn, std::string msg);
    void updateLoginStatus(bool isLoggedIn);
    bool isLoggedIn() const;
    bool isSubscribed() const;

  private:
    std::unique_ptr<IRtmEventHandler> eventHandler_;
    IRtmClient* signalingEngine;
    std::string appId;
    std::string token;
    std::string uid;
    std::string channelName;
    json config;
    bool isLoggedIn_;
    bool isSubscribed_;
};

class DemoRtmEventHandler : public IRtmEventHandler {
  public:
    DemoRtmEventHandler(SignalingManager* manager);
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