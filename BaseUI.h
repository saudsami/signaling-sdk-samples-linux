#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator>
#include "SignalingManager.h"

class BaseUI
{
public:
    BaseUI(SignalingManager &manager);
    virtual ~BaseUI();

    virtual void showHeader();
    virtual void showCommandList();
    virtual void processCommand(std::string input);
    virtual void run();

protected:
    SignalingManager &signalingManager;
};
