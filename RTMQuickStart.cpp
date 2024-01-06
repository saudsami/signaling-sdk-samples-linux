#include <sstream>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <fstream> 
#include <nlohmann/json.hpp>

#include "SignalingManager.h"

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

SignalingManager signalingManager;

void mainMenu() {
    bool quit  = false;
    while (!quit) {
      std::cout << WHITE 
                << "1: log in to Signaling\n"
                << "2: subcribe to a channel\n"
                << "3: unsubcribe from the channel\n"
                << "4: publish message\n"
                << "5: logout" <<std::endl;
      std::cout << YELLOW <<"please input your choice" << std::endl;
      std::string input;
      std::getline(std::cin, input);
      int32_t choice = 0;
      try {
        choice = std::stoi(input);
      } catch(...) {
        std::cout <<RED << "invalid input" << std::endl;
        continue;
      }
      switch (choice)
      {
        case 1: {
          std::cout << YELLOW << "Logging in to Signaling..." << std::endl;
          signalingManager.login();
        }
        break;
        case 2: {
          std::cout << YELLOW << "please input dst channel id" << std::endl;
          std::string dst;
          std::getline(std::cin, dst);
          signalingManager.subscribeChannel(dst);
        }
        break;
        case 3: {
          std::cout << YELLOW << "please input dst channel id" << std::endl;
          std::string dst;
          std::getline(std::cin, dst);
          signalingManager.unsubscribeChannel(dst);
        }
        break;
        case 4: {
          std::cout << YELLOW << "Type your message: ";
          std::string message;
          std::getline(std::cin, message);
          signalingManager.publishMessage("", message);
        }
        break;
        case 5: {
          signalingManager.logout();
          return;
        }
        break;
        default:
        break;
      }
    }
 }

void showCommandList() {
  std::cout << GREEN << "Choose from the following commands:\n"
    << YELLOW << "login" << GREEN << " Log in to Signaling\n"
    << YELLOW << "subscribe <channelName>" << GREEN << " Subscribe to a Signaling channel\n"
    << YELLOW << "unsubscribe <channelName>" << GREEN << " Unsubscribe from a Signaling channel\n"
    << YELLOW << "send <channelName> <message>" << GREEN << " Send a <message> to a <channelName> \n"
    << YELLOW << "logout" << GREEN << " Log out of Signaling\n"
    << YELLOW << "quit" << GREEN << " Exit this demo\n";
}

void processCommand(std::string input) {
    std::istringstream iss(input);
        std::vector<std::string> tokens(std::istream_iterator<std::string>{iss},
                                        std::istream_iterator<std::string>());
    if (tokens.empty()) {
        std::cout << "Invalid command. Please enter a valid command.\n";
        return;
    }

    const std::string& command = tokens[0];

    if (command == "login") {
        signalingManager.login();
    } else if (command == "subscribe" && tokens.size() > 1) {
        signalingManager.subscribeChannel(tokens[1]);
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
        std::cout << "Unknown command. Please enter a valid command.\n";
    }
}

int main(int argc, const char * argv[]) {   
  std::cout << MAGENTA << "\nWelcome to the Signaling Quickstart demo.\n";
  showCommandList();

   while (true) {
        std::cout << ">> ";
        std::string input;
        std::getline(std::cin, input);
        processCommand(input);
    }

    return 0;
}
  