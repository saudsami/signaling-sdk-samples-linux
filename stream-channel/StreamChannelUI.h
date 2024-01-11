#pragma once

#include "../authentication-workflow/AuthenticationWorkflowUI.h"
#include "SignalingManagerStreamChannel.h"

class StreamChannelUI : public AuthenticationWorkflowUI
{
public:
    StreamChannelUI(SignalingManagerStreamChannel &manager);
    void showHeader() override;
    void showCommandList() override;
    void processCommand(std::string input) override;

private:
    SignalingManagerStreamChannel &signalingManagerStreamChannel;
};
