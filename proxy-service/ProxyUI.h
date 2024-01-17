#pragma once

#include "../authentication-workflow/AuthenticationWorkflowUI.h"
#include "SignalingManagerProxy.h"

class ProxyUI : public AuthenticationWorkflowUI
{
public:
    ProxyUI(SignalingManagerProxy &manager);
    void showHeader() override;

private:
    SignalingManagerProxy &signalingManagerProxy;
};
