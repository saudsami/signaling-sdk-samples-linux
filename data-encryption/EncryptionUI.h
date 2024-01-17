#pragma once

#include "../authentication-workflow/AuthenticationWorkflowUI.h"
#include "SignalingManagerEncryption.h"

class EncryptionUI : public AuthenticationWorkflowUI
{
public:
    EncryptionUI(SignalingManagerEncryption &manager);
    void showHeader() override;

private:
    SignalingManagerEncryption &signalingManagerEncryption;
};
