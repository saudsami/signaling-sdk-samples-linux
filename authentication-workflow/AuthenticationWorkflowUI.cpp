#include "AuthenticationWorkflowUI.h"
#include "../TerminalColors.h"

AuthenticationWorkflowUI::AuthenticationWorkflowUI(SignalingManagerAuthentication &signalingManager)
    : BaseUI(signalingManager), signalingManagerAuthentication(signalingManager)
{
  // Additional initialization if needed
}

void AuthenticationWorkflowUI::showHeader()
{
  std::cout << MAGENTA << "\nWelcome to the Signaling Authentication demo.\n";
}

void AuthenticationWorkflowUI::showCommandList()
{
  std::cout << GREEN << "Choose from the following commands:\n"
            << YELLOW << "login <userId>" << GREEN << " Acquire a token for <UserId> and log in to Signaling\n"
            << YELLOW << "subscribe <channelName>" << GREEN << " Subscribe to a Messaging channel\n"
            << YELLOW << "unsubscribe <channelName>" << GREEN << " Unsubscribe from a Messaging channel\n"
            << YELLOW << "send <channelName> <message>" << GREEN << " Send a <message> to a <channelName> \n"
            << YELLOW << "logout" << GREEN << " Log out of Signaling\n"
            << YELLOW << "quit" << GREEN << " Exit this demo\n";
}

void AuthenticationWorkflowUI::processCommand(std::string input)
{
  std::istringstream iss(input);
  std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
                                  std::istream_iterator<std::string>());
  if (tokens.empty())
  {
    std::cout << "Invalid command. Please enter a valid command.\n";
    return;
  }

  const std::string &command = tokens[0];

  if (command == "login" && tokens.size() > 1)
  {
    if (signalingManager.isLoggedIn())
    {
      std::cout << RED << "You are already logged in.\n";
    }
    else
    {
      signalingManagerAuthentication.loginWithToken(tokens[1]);
    }
  }
  else if (command == "subscribe" && tokens.size() > 1)
  {
    if (signalingManager.isLoggedIn())
    {
      signalingManager.subscribeChannel(tokens[1]);
    }
    else
    {
      std::cout << RED << "You need to log in first.\n";
    }
  }
  else if (command == "unsubscribe" && tokens.size() > 1)
  {
    signalingManager.unsubscribeChannel(tokens[1]);
  }
  else if (command == "send" && tokens.size() > 2)
  {
    std::string message = input.substr(input.find(tokens[1]) + tokens[1].length());
    signalingManager.publishMessage(tokens[1], message);
  }
  else if (command == "logout")
  {
    signalingManager.logout();
  }
  else if (command == "quit")
  {
    std::cout << "Quitting the program.\n";
    exit(0);
  }
  else
  {
    std::cout << RED << "Invalid command. Please enter a valid command.\n";
  }
}