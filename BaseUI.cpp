#include "BaseUI.h"

// Terminal color codes for UBUNTU/LINUX
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

BaseUI::BaseUI(SignalingManager& manager) : signalingManager(manager) {

}

BaseUI::~BaseUI() {}

void BaseUI::showHeader() {
    std::cout << MAGENTA << "\nWelcome to the Signaling Quickstart demo.\n";
}

void BaseUI::showCommandList() {
    std::cout << GREEN << "Choose from the following commands:\n"
        << YELLOW << "login" << GREEN << " Log in to Signaling\n"
        << YELLOW << "subscribe <channelName>" << GREEN << " Subscribe to a Signaling channel\n"
        << YELLOW << "unsubscribe <channelName>" << GREEN << " Unsubscribe from a Signaling channel\n"
        << YELLOW << "send <channelName> <message>" << GREEN << " Send a <message> to a <channelName> \n"
        << YELLOW << "logout" << GREEN << " Log out of Signaling\n"
        << YELLOW << "quit" << GREEN << " Exit this demo\n";
}

void BaseUI::processCommand(std::string input) {
    std::istringstream iss(input);
        std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
                                        std::istream_iterator<std::string>());
    if (tokens.empty()) {
        std::cout << "Invalid command. Please enter a valid command.\n";
        return;
    }

    const std::string& command = tokens[0];

    if (command == "login") {
      if (signalingManager.isLoggedIn()){
        std::cout << RED << "You are already logged in.\n";
      } else {
        signalingManager.login();
      }
    } else if (command == "subscribe" && tokens.size() > 1) {
      if (signalingManager.isLoggedIn()){
        signalingManager.subscribeChannel(tokens[1]);  
      } else {
        std::cout << RED << "You need to log in first.\n";
      }
    } else if (command == "unsubscribe" && tokens.size() > 1) {
        signalingManager.unsubscribeChannel(tokens[1]);
    } else if (command == "send" && tokens.size() > 2) {
        std::string message = input.substr(input.find(tokens[1]) + tokens[1].length());
        signalingManager.publishMessage(tokens[1], message);
    } else if (command == "logout") {
        signalingManager.logout();
    } else if (command == "quit") {
        std::cout << "Quitting the program.\n";
        exit(0);
    } else {
        std::cout << RED << "Invalid command. Please enter a valid command.\n";
    }
}

void BaseUI::run() {
    showHeader();
    showCommandList();

    while (true) {
        std::cout << ">> ";
        std::string input;
        std::getline(std::cin, input);
        processCommand(input);
    }
}