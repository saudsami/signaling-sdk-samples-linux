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
            << YELLOW << "setLock <lockName>" << GREEN << " Create and configure a lock\n"
            << YELLOW << "acquireLock <lockName>" << GREEN << " Obtain the right to use a lock\n"
            << YELLOW << "releaseLock <lockName>" << GREEN << " Release a lock when you are done using it\n"
            << YELLOW << "removeLock <lockName>" << GREEN << " Delete a lock\n"
            << YELLOW << "getLocks <channelName>" << GREEN << " Query the number, name, and other information about locks in a channel\n"
            << GREEN << "Manage metadata:\n"
            << YELLOW << "getChannelMetadata <channelName>" << GREEN << "  Obtain the metadata of the specified channel\n"
            << YELLOW << "setChannelMetadata <key> <value> [<revision>] [<lockName>]" << GREEN << " Set a key-value pair in the channel metadata\n"
            << YELLOW << "updateChannelMetadata <key> <value> [<revision>] [<lockName>]" << GREEN << " Update a value in the channel metadata\n"
            << YELLOW << "removeChannelMetadata <key>" << GREEN << " Remove a key-value pair in the channel metadata\n"
            << YELLOW << "getUserMetadata <userId>" << GREEN << "  Obtain the metadata of the specified user\n"
            << YELLOW << "setUserMetadata <key> <value> [<revision>]" << GREEN << " Set a key-value pair in the user metadata\n"
            << YELLOW << "removeUserMetadata <userId>" << GREEN << " Remove the specified key from the metadata of the user\n"
            << YELLOW << "subscribeUserMetadata <userId>" << GREEN << " Subscribe to receive metadata change notifications\n"
            << YELLOW << "unsubscribeUserMetadata <userId>" << GREEN << " Unsubscribe to stop receiving metadata change notifications\n";
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
    signalingManagerStorage.acquireLock(tokens[1]);
  }
  else if (command == "releaseLock" && tokens.size() > 1)
  {
    signalingManagerStorage.releaseLock(tokens[1]);
  }
  else if (command == "removeLock" && tokens.size() > 1)
  {
    signalingManagerStorage.removeLock(tokens[1]);
  }
  else if (command == "getLocks" && tokens.size() > 1)
  {
    signalingManagerStorage.getLocks(tokens[1]);
  }
  else if (command == "getChannelMetadata" && tokens.size() > 1)
  {
    signalingManagerStorage.getChannelMetadata(tokens[1]);
  }
  else if (command == "getUserMetadata" && tokens.size() > 1)
  {
    signalingManagerStorage.getUserMetadata(tokens[1]);
  }
  else if (command == "setChannelMetadata" && tokens.size() > 2)
  {
    int64_t revision = -1;
    std::string lockName = "";

    if (tokens.size() > 4)
      lockName = tokens[4];
    if (tokens.size() > 3)
      revision = std::stoll(tokens[3]);

    signalingManagerStorage.setChannelMetadata(tokens[1], tokens[2], revision, lockName);
  }
  else if (command == "updateChannelMetadata" && tokens.size() > 2)
  {
    int64_t revision = -1;
    std::string lockName = "";

    if (tokens.size() > 4)
      lockName = tokens[4];
    if (tokens.size() > 3)
      revision = std::stoll(tokens[3]);

    signalingManagerStorage.updateChannelMetadata(tokens[1], tokens[2], revision, lockName);
  }
  else if (command == "removeChannelMetadata" && tokens.size() > 1)
  {
    signalingManagerStorage.removeChannelMetadata(tokens[1]);
  }
  else if (command == "setUserMetadata" && tokens.size() > 2)
  {
    int64_t revision = -1;
    if (tokens.size() > 3)
      revision = std::stoll(tokens[3]);

    signalingManagerStorage.setUserMetadata(tokens[1], tokens[2], revision);
  }
  else if (command == "removeUserMetadata" && tokens.size() > 1)
  {
    signalingManagerStorage.removeUserMetadata(tokens[1]);
  }
  else if (command == "subscribeUserMetadata" && tokens.size() > 1)
  {
    signalingManagerStorage.subscribeUserMetadata(tokens[1]);
  }
  else if (command == "unsubscribeUserMetadata" && tokens.size() > 1)
  {
    signalingManagerStorage.unsubscribeUserMetadata(tokens[1]);
  }
  else
  {
    AuthenticationWorkflowUI::processCommand(input);
  }
}