#include "SignalingManager.h"
#include "IAgoraRtmClient.h"

using namespace agora::rtm;
using json = nlohmann::json;

// Implementation of DemoRtmEventHandler
void DemoRtmEventHandler::onLoginResult(RTM_ERROR_CODE errorCode) {
    cbPrint("onLogin: errorCode: %d", errorCode);
}

void DemoRtmEventHandler::onConnectionStateChanged(const char *channelName, RTM_CONNECTION_STATE state, RTM_CONNECTION_CHANGE_REASON reason) {
    cbPrint("onConnectionStateChanged: %d", state);
}

void DemoRtmEventHandler::onPublishResult(const uint64_t requestId, RTM_ERROR_CODE errorCode) {
    cbPrint("onPublishResult request id: %lld result: %d", requestId, errorCode);
}

void DemoRtmEventHandler::onMessageEvent(const MessageEvent &event) {
    cbPrint("receive message from: %s, message: %s", event.publisher, event.message);
}

void DemoRtmEventHandler::onSubscribeResult(const uint64_t requestId, const char *channelName, RTM_ERROR_CODE errorCode) {
    cbPrint("onSubscribeResult: channel:%s, request id: %lld result: %d", channelName, requestId, errorCode);
}

void DemoRtmEventHandler::cbPrint(const char* fmt, ...) {
    printf("\x1b[32m<< RTM async callback: ");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf(" >>\x1b[0m\n");
}

// Implementation of SignalingManager
SignalingManager::SignalingManager()
    : eventHandler_(new DemoRtmEventHandler()),
      signalingEngine(nullptr) {
    Init();
}

  void SignalingManager::Init() {
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

    // Create an IRtmClient instance
    signalingEngine = createAgoraRtmClient();
    if (!signalingEngine) {
      std::cout << "error creating rtm service!" << std::endl;
      exit(0);
    }
  }

  void SignalingManager::login() {
      RtmConfig cfg;
      cfg.appId = appId.c_str();
      cfg.userId = uid.c_str();
      cfg.eventHandler = eventHandler_.get();
      
      // Initialize an IRtmClient instance
      int ret = signalingEngine->initialize(cfg);
      std::cout << "login ret: " << ret << std::endl;
      
      // Log in the RTM server
      if (ret) {
        std::cout << "error initializing rtm service: " << ret << std::endl;
        exit(0);
      }
  }

  // Log out from the RTM server
  void SignalingManager::logout() {
    int ret = signalingEngine->logout();
    std::cout << "logout ret: " << ret << std::endl;
  }

  // Subscribe to a channel
  void SignalingManager::subscribeChannel(std::string& chnId) {
    SubscribeOptions opt = SubscribeOptions();
    uint64_t req_id;
    int ret = signalingEngine->subscribe(chnId.c_str(), opt, req_id);
    std::cout << "subscribe channel ret:" << ret << std::endl;
  }

  // Unsubscribe from a channel
  void SignalingManager::unsubscribeChannel(std::string& chnId) {
    uint64_t req_id;
    int ret = signalingEngine->unsubscribe(chnId.c_str());
    std::cout << "unsubscribe channel ret:" << ret << std::endl;
  }
  // Publish a message
  void SignalingManager::publishMessage(std::string& chn, std::string& msg) {
    PublishOptions opt;
    opt.messageType = RTM_MESSAGE_TYPE_STRING;
    uint64_t req_id;
    int ret = signalingEngine->publish(chn.c_str(), msg.c_str(), msg.size(), opt, req_id);
    std::cout << "publishMessage ret:" << ret << "request id: %lld" << req_id << std::endl;
  }

