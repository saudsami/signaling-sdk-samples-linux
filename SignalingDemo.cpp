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

#include "QuickstartUI.h"
#include "AuthenticationWorkflowUI.h"
#include "PresenceUI.h"
#include "StreamChannelUI.h"

void mainMenu()
{
  bool quit = false;
  while (!quit)
  {
    std::cout << WHITE << "1: SDK quickstart\n"
              << "2: Token authentication\n"
              << "3: Presence\n"
              << "4: Stream channels\n"
              << "5: Presence\n"
              << "0: Exit\n"
              << std::endl;
    std::cout << YELLOW << "Choose an example: ";
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
      StreamChannelUI StreamChannelUI(signalingManager);
      StreamChannelUI.run();
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
