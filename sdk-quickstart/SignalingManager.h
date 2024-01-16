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

class SignalingManager
{
public:
  SignalingManager();
  virtual void Init();
  virtual void login();
  virtual void logout();
  virtual void subscribeChannel(std::string chnId);
  virtual void unsubscribeChannel(std::string chnId);
  virtual void publishMessage(std::string chn, std::string msg);
  void updateLoginStatus(bool isLoggedIn);
  bool isLoggedIn() const;
  bool isSubscribed() const;
  static std::string getConnectionStateDescription(int connectionState);

protected:
  IRtmClient *signalingEngine;
  json config;
  std::unique_ptr<IRtmEventHandler> eventHandler_;
  std::string appId;
  std::string token;
  std::string uid;
  std::string channelName;
  RTM_CHANNEL_TYPE channelType = RTM_CHANNEL_TYPE_MESSAGE;

private:
  bool isLoggedIn_;
  bool isSubscribed_;
};
