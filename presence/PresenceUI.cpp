#include "PresenceUI.h"
#include "../TerminalColors.h"

PresenceUI::PresenceUI(SignalingManagerPresence& signalingManager)
    : AuthenticationWorkflowUI(signalingManager), signalingManagerPresence(signalingManager) {
    // Additional initialization if needed
}

void PresenceUI::showHeader() {
    std::cout << MAGENTA << "\nWelcome to the Signaling Presence demo.\n";
}

void PresenceUI::showCommandList() {
    AuthenticationWorkflowUI::showCommandList();

    std::cout << "Presence commands:\n"
        << YELLOW << "getOnlineUsers <channelName>" << GREEN << "  Query information about online users in a channel\n"
        << YELLOW << "getUserChannels <userId>" << GREEN << " List channels that a specified user has subscribed to or joined\n"
        << YELLOW << "setState <userId>" << GREEN << " Customize the temporary user state\n"
        << YELLOW << "getState <channelName>" << GREEN << " Get the temporary user state of a specified user\n"
        << YELLOW << "removeState" << GREEN << " Remove one or more of your temporary states \n";
}
void PresenceUI::processCommand(std::string input) {
    std::istringstream iss(input);
    std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
                                        std::istream_iterator<std::string>());
    if (tokens.empty()) {
        std::cout << "Invalid command. Please enter a valid command.\n";
        return;
    }

    const std::string& command = tokens[0];

    if (command == "getOnlineUsers" && tokens.size() > 1) {
        signalingManagerPresence.getOnlineUsers(tokens[1]);  
    } else if (command == "getUserChannels" && tokens.size() > 1) {
        signalingManagerPresence.getUserChannels(tokens[1]);  
    } else {
        AuthenticationWorkflowUI::processCommand(input);
    }
}