#include "BaseSignalingEventHandler.h"
#include "SignalingManager.h"
#include "IAgoraRtmClient.h"

using namespace agora::rtm;
using json = nlohmann::json;

// Implementation of SignalingManager
SignalingManager::SignalingManager()
    : eventHandler_(new BaseSignalingEventHandler(this)),
      signalingEngine(nullptr)
{
  Init();
}

void SignalingManager::Init()
{
  // Open the JSON file
  std::ifstream configFile("config.json");

  // Check if the file is open
  if (!configFile.is_open())
  {
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
  if (!signalingEngine)
  {
    std::cout << "Error creating Signaling service!" << std::endl;
    exit(0);
  }
  else
  {
    // Success creating an IRtmClient instance
  }
}

bool SignalingManager::isLoggedIn() const
{
  return isLoggedIn_;
}

bool SignalingManager::isSubscribed() const
{
  return isSubscribed_;
}

void SignalingManager::login()
{
  RtmConfig rtmConfig;
  rtmConfig.appId = appId.c_str();
  rtmConfig.userId = uid.c_str();
  rtmConfig.presenceTimeout = config["presenceTimeout"];
  rtmConfig.eventHandler = eventHandler_.get();

  // Initialize the signalingEngine
  int ret = signalingEngine->initialize(rtmConfig);
  std::cout << "initialize returned: " << ret << std::endl;
  
  if (ret)
  {
    std::cout << "Error initializing Signaling service: " << ret << std::endl;
    exit(0);
  }

  // Log in using the token
  ret = signalingEngine->login(token.c_str());
  if (ret)
  {
    std::cout << "login failed: " << ret << std::endl;
    exit(0);
  }
  else
  {
    std::cout << "login returned: " << ret << std::endl;
  }
}

// Log out from the RTM server
void SignalingManager::logout()
{
  int ret = signalingEngine->logout();
  std::cout << "logout returned:  " << ret << std::endl;
}

// Subscribe to a channel
void SignalingManager::subscribeChannel(std::string chnId)
{
  channelType = RTM_CHANNEL_TYPE_MESSAGE;
  SubscribeOptions opt = SubscribeOptions();
  uint64_t requestId;
  int ret = signalingEngine->subscribe(chnId.c_str(), opt, requestId);
  std::cout << "subscribe channel returned: " << ret << std::endl;
  if (ret == 0) channelName = chnId;
}

// Unsubscribe from a channel
void SignalingManager::unsubscribeChannel(std::string chnId)
{
  uint64_t requestId;
  int ret = signalingEngine->unsubscribe(chnId.c_str());
  std::cout << "unsubscribe channel returned: " << ret << std::endl;
}
// Publish a message
void SignalingManager::publishMessage(std::string chn, std::string msg)
{
  if (chn.empty())
  {
    // Assign the default value from the config file
    chn = channelName;
  }

  PublishOptions opt;
  opt.messageType = RTM_MESSAGE_TYPE_STRING;
  uint64_t requestId;
  int ret = signalingEngine->publish(chn.c_str(), msg.c_str(), msg.size(), opt, requestId);
  std::cout << "publishMessage returned: " << ret << std::endl;
}

void SignalingManager::updateLoginStatus(bool isLoggedIn)
{
  isLoggedIn_ = isLoggedIn;
}

std::string SignalingManager::getConnectionStateDescription(int connectionState)
{
  switch (connectionState)
  {
  case 1:
    return "Disconnected from the server.";
  case 2:
    return "Connecting to the server.";
  case 3:
    return "Connected to the server.";
  case 4:
    return "Reconnecting to the server.";
  case 5:
    return "Cannot connect to the server.";
  default:
    return "Unknown connection state: " + std::to_string(connectionState);
  }
}