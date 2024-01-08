#include "MyRtmEventHandler.h"
#include "SignalingManager.h"
#include "IAgoraRtmClient.h"

using namespace agora::rtm;
using json = nlohmann::json;


// Implementation of SignalingManager
SignalingManager::SignalingManager()
    : eventHandler_(new MyRtmEventHandler(this)),
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
    channelName = config["channelName"];
    isLoggedIn_ = false;
    isSubscribed_ = false;

    // Create an IRtmClient instance
    signalingEngine = createAgoraRtmClient();
    if (!signalingEngine) {
      std::cout << "Error creating Signaling service!" << std::endl;
      exit(0);
    } else {
      // Success creating an IRtmClient instance
    }
  }

  bool SignalingManager::isLoggedIn() const {
      return isLoggedIn_;
  }

  bool SignalingManager::isSubscribed() const {
      return isSubscribed_;
  }

  void SignalingManager::login() {
      RtmConfig cfg;
      cfg.appId = appId.c_str();
      cfg.userId = uid.c_str();
      cfg.eventHandler = eventHandler_.get();
      
      // Initialize the signalingEngine
      int ret = signalingEngine->initialize(cfg);
      std::cout << "Initialize returned: " << ret << std::endl;
      if (ret) {
        std::cout << "Error initializing Signaling service: " << ret << std::endl;
        exit(0);
      }
      
      // Log in using the token
      ret = signalingEngine->login(token.c_str());
      std::cout << "Login returned:" << ret << std::endl;
      if (ret) {
        std::cout << "Login failed: " << ret << std::endl;
        exit(0);
      }
  }

  // Log out from the RTM server
  void SignalingManager::logout() {
    int ret = signalingEngine->logout();
    std::cout << "logout ret: " << ret << std::endl;
  }

  // Subscribe to a channel
  void SignalingManager::subscribeChannel(std::string chnId) {
    SubscribeOptions opt = SubscribeOptions();
    uint64_t req_id;
    int ret = signalingEngine->subscribe(chnId.c_str(), opt, req_id);
    std::cout << "subscribe channel ret:" << ret << std::endl;
  }

  // Unsubscribe from a channel
  void SignalingManager::unsubscribeChannel(std::string chnId) {
    uint64_t req_id;
    int ret = signalingEngine->unsubscribe(chnId.c_str());
    std::cout << "unsubscribe channel ret:" << ret << std::endl;
  }
  // Publish a message
  void SignalingManager::publishMessage(std::string chn, std::string msg) {
    if (chn.empty()) {
        // Assign the default value from the config file
        chn = channelName;
    }

    PublishOptions opt;
    opt.messageType = RTM_MESSAGE_TYPE_STRING;
    uint64_t req_id;
    int ret = signalingEngine->publish(chn.c_str(), msg.c_str(), msg.size(), opt, req_id);
    std::cout << "publishMessage ret:" << ret << " request id: %llu" << req_id << std::endl;
  }

  void SignalingManager::updateLoginStatus(bool isLoggedIn) {
      isLoggedIn_ = isLoggedIn;
  }