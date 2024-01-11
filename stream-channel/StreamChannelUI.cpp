#include "StreamChannelUI.h"
#include "../TerminalColors.h"

StreamChannelUI::StreamChannelUI(SignalingManagerStreamChannel &signalingManager)
    : AuthenticationWorkflowUI(signalingManager), signalingManagerStreamChannel(signalingManager)
{
  // Additional initialization if needed
}

void StreamChannelUI::showHeader()
{
  std::cout << MAGENTA << "\nWelcome to the Signaling Stream Channel demo.\n";
}

void StreamChannelUI::showCommandList()
{
  AuthenticationWorkflowUI::showCommandList();

  std::cout << WHITE << "Stream Channel commands:\n"
            << YELLOW << "join <channelName>" << GREEN << "  Create and join a Stream channel\n"
            << YELLOW << "leave <channelName>" << GREEN << " Leave a Stream channel\n"
            << YELLOW << "joinTopic <topicName> <key> <value>" << GREEN << " Join a topic to send messages\n"
            << YELLOW << "subscribeTopic <topicName> <key>" << GREEN << " Subscribe to a topic to receive messages \n"
            << YELLOW << "leaveTopic <topicName> <userId>" << GREEN << " Leave a topic\n";
            
}
void StreamChannelUI::processCommand(std::string input)
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

  if (command == "join" && tokens.size() > 1)
  {
    signalingManagerStreamChannel.joinStreamChannel(tokens[1]);
  }
  else if (command == "leave" && tokens.size() > 1)
  {
    signalingManagerStreamChannel.leaveStreamChannel(tokens[1]);
  }
  else if (command == "joinTopic" && tokens.size() > 1)
  {
    signalingManagerStreamChannel.joinTopic(tokens[1]);
  }
  else if (command == "subscribeTopic" && tokens.size() > 1)
  {
    signalingManagerStreamChannel.subscribeTopic(tokens[1]);
  }
  else if (command == "leaveTopic" && tokens.size() > 1)
  {
    signalingManagerStreamChannel.leaveTopic(tokens[1]);
  }
  else
  {
    AuthenticationWorkflowUI::processCommand(input);
  }
}