#pragma once

#include "../authentication-workflow/AuthenticationWorkflowUI.h"
#include "SignalingManagerPresence.h"

class PresenceUI : public AuthenticationWorkflowUI
{
public:
    PresenceUI(SignalingManagerPresence &manager);
    void showHeader() override;
    void showCommandList() override;
    void processCommand(std::string input) override;

private:
    SignalingManagerPresence &signalingManagerPresence;
};
