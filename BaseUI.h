// BaseUI.h
#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator>
#include "SignalingManager.h"

class BaseUI {
public:
    BaseUI(SignalingManager& manager);
    virtual ~BaseUI();

    void showHeader();
    void showCommandList();
    void processCommand(std::string input);
    void run();

protected:
    SignalingManager& signalingManager;
};
