#include "BaseUI.h"
#include "TerminalColors.h"

BaseUI::BaseUI(SignalingManager &manager) : signalingManager(manager)
{
}

BaseUI::~BaseUI() {}

void BaseUI::showHeader()
{
  std::cout << MAGENTA << "\nWelcome to the Signaling Quickstart demo.\n";
}

void BaseUI::showCommandList()
{
  std::cout << WHITE << "Choose from the following commands:\n"
            << YELLOW << "login" << GREEN << " Log in to Signaling\n"
            << YELLOW << "subscribe <channelName>" << GREEN << " Subscribe to a Messaging channel\n"
            << YELLOW << "unsubscribe <channelName>" << GREEN << " Unsubscribe from a Messaging channel\n"
            << YELLOW << "send <channelName> <message>" << GREEN << " Send a <message> to a <channelName> \n"
            << YELLOW << "logout" << GREEN << " Log out of Signaling\n"
            << YELLOW << "quit" << GREEN << " Exit this demo\n";
}

void BaseUI::processCommand(std::string input)
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

  if (command == "login")
  {
    if (signalingManager.isLoggedIn())
    {
      std::cout << RED << "You are already logged in.\n";
    }
    else
    {
      signalingManager.login();
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
    std::cout << "Exiting the demo.\n";
    exit(0);
  }
  else
  {
    std::cout << RED << "Invalid command. Please enter a valid command.\n";
  }
}

void BaseUI::run()
{
  showHeader();
  showCommandList();

  while (true)
  {
    std::cout << WHITE << "> ";
    std::string input;
    std::getline(std::cin, input);
    processCommand(input);
  }
}