#pragma once

#include "../BaseUI.h"
#include "SignalingManagerAuthentication.h"

class AuthenticationWorkflowUI : public BaseUI
{
public:
    AuthenticationWorkflowUI(SignalingManagerAuthentication &manager);
    void showHeader() override;
    void showCommandList() override;
    void processCommand(std::string input) override;

private:
    SignalingManagerAuthentication &signalingManagerAuthentication;
};
