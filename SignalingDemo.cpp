#include <sstream>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <fstream>
#include <nlohmann/json.hpp>
#include "TerminalColors.h"

#include "SignalingManager.h"
#include "SignalingManagerAuthentication.h"
#include "SignalingManagerPresence.h"
#include "SignalingManagerStreamChannel.h"
#include "SignalingManagerStorage.h"
#include "SignalingManagerEncryption.h"
#include "SignalingManagerGeofencing.h"
#include "SignalingManagerProxy.h"

#include "QuickstartUI.h"
#include "AuthenticationWorkflowUI.h"
#include "PresenceUI.h"
#include "StreamChannelUI.h"
#include "StorageUI.h"
#include "EncryptionUI.h"
#include "GeofencingUI.h"
#include "ProxyUI.h"

void mainMenu()
{
  bool quit = false;
  while (!quit)
  {
    std::cout << MAGENTA "Welcome to the Signaling demo for Linux C++:\n"
              << WHITE
              << "1: SDK quickstart\n"
              << "2: Token authentication\n"
              << "3: Presence\n"
              << "4: Stream channels\n"
              << "5: Storage\n"
              << "6: Data encryption\n"
              << "7: Geofencing\n"
              << "8: Proxy service\n"
              << "0: Exit\n"
              << std::endl;
    std::cout << YELLOW << "Choose a sample project: ";
    std::string input;
    std::getline(std::cin, input);
    int32_t choice = 0;
    try
    {
      choice = std::stoi(input);
    }
    catch (...)
    {
      std::cout << RED << "Invalid selection" << std::endl;
      continue;
    }
    switch (choice)
    {
    case 1:
    { // SDK Quickstart
      SignalingManager signalingManager;
      QuickStartUI quickStartUI(signalingManager);
      quickStartUI.run();
    }
    break;
    case 2:
    { // Authentication
      SignalingManagerAuthentication signalingManager;
      AuthenticationWorkflowUI authenticationWorkflowUI(signalingManager);
      authenticationWorkflowUI.run();
    }
    break;
    case 3:
    {
      SignalingManagerPresence signalingManager;
      PresenceUI presenceUI(signalingManager);
      presenceUI.run();
    }
    break;
    case 4:
    {
      SignalingManagerStreamChannel signalingManager;
      StreamChannelUI streamChannelUI(signalingManager);
      streamChannelUI.run();
    }
    case 5:
    {
      SignalingManagerStorage signalingManager;
      StorageUI storageUI(signalingManager);
      storageUI.run();
    }
    case 6:
    {
      SignalingManagerEncryption signalingManager;
      EncryptionUI encryptionUI(signalingManager);
      encryptionUI.run();
    }
    break;
    case 7:
    {
      SignalingManagerGeofencing signalingManager;
      GeofencingUI geofencingUI(signalingManager);
      geofencingUI.run();
    }
    break;
    case 8:
    {
      SignalingManagerProxy signalingManager;
      ProxyUI proxyUI(signalingManager);
      proxyUI.run();
    }
    break;
    case 0:
    {

      return;
    }
    break;
    default:
      break;
    }
  }
}

int main(int argc, const char *argv[])
{
  mainMenu();
  return 0;
}
