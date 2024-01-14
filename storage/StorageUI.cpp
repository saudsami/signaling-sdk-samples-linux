#include "StorageUI.h"
#include "../TerminalColors.h"

StorageUI::StorageUI(SignalingManagerStorage &signalingManager)
    : AuthenticationWorkflowUI(signalingManager), signalingManagerStorage(signalingManager)
{
  // Additional initialization if needed
}

void StorageUI::showHeader()
{
  std::cout << MAGENTA << "\nWelcome to the Signaling Storage demo.\n";
}

void StorageUI::showCommandList()
{
  AuthenticationWorkflowUI::showCommandList();

  std::cout << WHITE << "Storage commands\n"
            << GREEN << "Manage locks:\n"
            << YELLOW << "setLock <lockName>" << GREEN << " Set a lock\n"
            << YELLOW << "acquireLock <lockName>" << GREEN << " Acquire a lock\n"
            << YELLOW << "releaseLock <lockName>" << GREEN << " Release a lock\n"
            << YELLOW << "removeLock <lockName>" << GREEN << " Remove a lock\n"
            << YELLOW << "getLock <lockName>" << GREEN << " Get a lock\n";
}
void StorageUI::processCommand(std::string input)
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

  if (command == "setLock" && tokens.size() > 1)
  {
    signalingManagerStorage.setLock(tokens[1]);
  }
  else if (command == "acquireLock" && tokens.size() > 1)
  {
    // signalingManagerStorage.getUserChannels(tokens[1]);
  }
  else if (command == "releaseLock" && tokens.size() > 2)
  {
    // signalingManagerStorage.getState(tokens[1], tokens[2]);
  }
  else if (command == "removeLock" && tokens.size() > 3)
  {
    // signalingManagerStorage.setState(tokens[1], tokens[2], tokens[3]);
  }
  else if (command == "getLock" && tokens.size() > 2)
  {
    // signalingManagerStorage.removeState(tokens[1], tokens[2]);
  }
  else
  {
    AuthenticationWorkflowUI::processCommand(input);
  }
}