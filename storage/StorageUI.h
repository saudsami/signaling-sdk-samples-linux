#pragma once

#include "../authentication-workflow/AuthenticationWorkflowUI.h"
#include "SignalingManagerStorage.h"

class StorageUI : public AuthenticationWorkflowUI
{
public:
    StorageUI(SignalingManagerStorage &manager);
    void showHeader() override;
    void showCommandList() override;
    void processCommand(std::string input) override;

private:
    SignalingManagerStorage &signalingManagerStorage;
};
