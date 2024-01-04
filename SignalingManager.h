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

class DemoRtmEventHandler : public IRtmEventHandler {
public:
    // Add the event listener
    void onLoginResult(RTM_ERROR_CODE errorCode) override;
    void onConnectionStateChanged(const char *channelName, RTM_CONNECTION_STATE state, RTM_CONNECTION_CHANGE_REASON reason) override;
    void onPublishResult(const uint64_t requestId, RTM_ERROR_CODE errorCode) override;
    void onMessageEvent(const MessageEvent &event) override;
    void onSubscribeResult(const uint64_t requestId, const char *channelName, RTM_ERROR_CODE errorCode) override;

private:
    void cbPrint(const char* fmt, ...);
};

class SignalingManager {
public:
    SignalingManager();
    void Init();
    void login();
    void logout();
    void subscribeChannel(std::string& chnId);
    void unsubscribeChannel(std::string& chnId);
    void publishMessage(std::string& chn, std::string& msg);

private:
    std::unique_ptr<IRtmEventHandler> eventHandler_;
    IRtmClient* signalingEngine;
    std::string appId;
    std::string token;
    std::string uid;
    json config;
};
