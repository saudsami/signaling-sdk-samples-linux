#include "IAgoraRtmClient.h"
#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <fstream> 
#include <nlohmann/json.hpp>

// Global variables
std::string appId;
std::string token;
std::string uid;
json config;

using namespace agora::rtm;
using json = nlohmann::json;

class DemoRtmEventHandler : public IRtmEventHandler {
public:
  // Add the event listener
  void onLoginResult(RTM_ERROR_CODE errorCode) override {
    cbPrint("onLogin: errorCode: %d", errorCode);
  }
  void onConnectionStateChanged(const char *channelName, RTM_CONNECTION_STATE state, RTM_CONNECTION_CHANGE_REASON reason) override {
    cbPrint("onConnectionStateChanged: %d", state);
  }
  void onPublishResult(const uint64_t requestId, RTM_ERROR_CODE errorCode) override {
    cbPrint("onPublishResult request id: %lld result: %d",requestId, errorCode);
  }
  void onMessageEvent(const MessageEvent &event) override {
    cbPrint("receive message from: %s, message: %s", event.publisher, event.message);
  }
  void onSubscribeResult(const uint64_t requestId, const char *channelName, RTM_ERROR_CODE errorCode) override {
    cbPrint("onSubscribeResult: channel:%s, request id: %lld result: %d", channelName, requestId, errorCode);
  }

private:
  void cbPrint(const char* fmt, ...) {
    printf("\x1b[32m<< RTM async callback: ");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf(" >>\x1b[0m\n");
  }
};

class SignalingManager {
public:
  SignalingManager()
    : eventHandler_(new DemoRtmEventHandler()),
      signalingEngine(nullptr) { Init(); }

  void Init() {
     // Open the JSON file
    std::ifstream configFile("config.json");

    // Check if the file is open
    if (!configFile.is_open()) {
        std::cerr << "Error opening config.json\n";
    }

    // Parse the JSON content
    configFile >> config;

    // Close the file
    configFile.close();

    // Read values from the JSON file
    appId = config["appId"];
    token = config["token"];
    uid = config["uid"];

    //std::cout << appId << std::endl;

    // Create an IRtmClient instance
    signalingEngine = createAgoraRtmClient();
    if (!signalingEngine) {
      std::cout << RED <<"error creating rtm service!" << std::endl;
      exit(0);
    }
}

  void login() {
    while (true) {
      RtmConfig cfg;
      cfg.appId = appId.c_str();
      cfg.userId = uid.c_str();
      cfg.eventHandler = eventHandler_.get();
      
      // Initialize an IRtmClient instance
      int ret = signalingEngine->initialize(cfg);
      // Log in the RTM server
      if (ret) {
        std::cout << RED <<  "error initializing rtm service: " << ret << std::endl;
        exit(0);
      }
      ret = signalingEngine->login(token.c_str());
      std::cout << BOLDBLUE << "login ret:" << ret << std::endl;
      if (ret) {
        login();
      }
      // Sample codes for the user interface
      mainMeun();
      std::cout << YELLOW << "quit ? yes/no" << std::endl;
      std::string input;
      std::getline(std::cin, input);
      if (input.compare("yes") == 0) {
        exit(0);
      }
    }
  }

  // Log out from the RTM server
  void logout() {
    int ret = signalingEngine->logout();
    std::cout << BOLDBLUE <<"logout ret: " << ret << std::endl;
  }

  // Subscribe to a channel
  void subscribeChannel(std::string& chnId) {
    SubscribeOptions opt = SubscribeOptions();
    uint64_t req_id;
    int ret = signalingEngine->subscribe(chnId.c_str(), opt, req_id);
    std::cout << BOLDBLUE << "subscribe channel ret:" << ret << std::endl;
  }

  // Unsubscribe from a channel
  void unsubscribeChannel(std::string& chnId) {
    uint64_t req_id;
    int ret = signalingEngine->unsubscribe(chnId.c_str());
    std::cout << BOLDBLUE << "unsubscribe channel ret:" << ret << std::endl;
  }
  // Publish a message
  void publishMessage(std::string& chn,
                            std::string& msg) {
    PublishOptions opt;
    opt.messageType = RTM_MESSAGE_TYPE_STRING;
    uint64_t req_id;
    int ret = signalingEngine->publish(chn.c_str(), msg.c_str(), msg.size(), opt, req_id);
    std::cout << BOLDBLUE << "publishMessage ret:" << ret << "request id: %lld" << req_id << std::endl;
  }

  // Sample codes for the user interface
  void mainMeun() {
    bool quit  = false;
    while (!quit) {
      std::cout << WHITE << "1: subcribe channel\n"
                << "2: unsubcribe channel\n"
                << "3: publish message\n"
                << "4: logout" <<std::endl;
      std::cout << YELLOW <<"please input your choice" << std::endl;
      std::string input;
      std::getline(std::cin, input);
      int32_t choice = 0;
      try {
        choice = std::stoi(input);
      } catch(...) {
        std::cout <<RED << "invalid input" << std::endl;
        continue;
      }
      switch (choice)
      {
        case 1: {
          std::cout << YELLOW << "please input dst channel id" << std::endl;
          std::string dst;
          std::getline(std::cin, dst);
          subscribeChannel(dst);
        }
        break;
        case 2: {
          std::cout << YELLOW << "please input dst channel id" << std::endl;
          std::string dst;
          std::getline(std::cin, dst);
          unsubscribeChannel(dst);
        }
        break;
        case 3: {
          std::cout << YELLOW << "please input channel id" << std::endl;
          std::string channel;
          std::getline(std::cin, channel);
          Chat(channel);
        }
        break;
        case 4: {
          logout();
          return;
        }
        break;
        default:
        break;
      }
    }
  }


  void Chat(std::string& channel) {
    std::string message;
    while (true) {
      std::cout << YELLOW << "please input message "
                << "or input \"quit\" to leave groupchat,"
                << std::endl;
      std::getline(std::cin, message);
      if (message.compare("quit") == 0) {
        return;
      } else {
        publishMessage(channel, message);
      }
    }
  }

private:
  std::unique_ptr<IRtmEventHandler> eventHandler_;
  IRtmClient* signalingEngine;
};
