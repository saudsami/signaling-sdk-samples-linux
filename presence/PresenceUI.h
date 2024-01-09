#pragma once

#include "../BaseUI.h"
#include "SignalingManagerPresence.h"

class PresenceUI : public BaseUI {
public:
    PresenceUI(SignalingManagerPresence& manager);
    void showHeader() override;
    void showCommandList() override;
    void processCommand(std::string input) override;

private:
    SignalingManagerPresence& signalingManagerPresence;
};
