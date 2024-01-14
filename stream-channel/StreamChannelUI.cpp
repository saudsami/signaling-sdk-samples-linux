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
  std::cout
      << WHITE << "Choose from the following commands:\n"
      << YELLOW << "login <userId>" << GREEN << " Acquire a token for <UserId> and log in to Signaling\n"
      << YELLOW << "join <channelName>" << GREEN << "  Create and join a Stream channel\n"
      << YELLOW << "leave <channelName>" << GREEN << " Leave a Stream channel\n"
      << YELLOW << "joinTopic <topicName>" << GREEN << " Join a topic to send messages\n"
      << YELLOW << "publishTopicMessage <topicName> <message>" << GREEN << " Send a <message> to a <topicName> \n"
      << YELLOW << "subscribeTopic <topicName> <publisherUserId>" << GREEN << " Subscribe to a topic to receive messages from the specified publisher\n"
      << YELLOW << "leaveTopic <topicName>" << GREEN << " Leave a topic\n"
      << YELLOW << "logout" << GREEN << " Log out of Signaling\n"
      << YELLOW << "quit" << GREEN << " Exit this demo\n";
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
    signalingManagerStreamChannel.subscribeTopic(tokens[1], tokens[2]);
  }
  else if (command == "leaveTopic" && tokens.size() > 1)
  {
    signalingManagerStreamChannel.leaveTopic(tokens[1]);
  }
  else if (command == "publishTopicMessage" && tokens.size() > 1)
  {
    signalingManagerStreamChannel.publishTopicMessage(tokens[1], tokens[2]);
  }
  else
  {
    AuthenticationWorkflowUI::processCommand(input);
  }
}