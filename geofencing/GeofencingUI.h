#pragma once

#include "../authentication-workflow/AuthenticationWorkflowUI.h"
#include "SignalingManagerGeofencing.h"

class GeofencingUI : public AuthenticationWorkflowUI
{
public:
    GeofencingUI(SignalingManagerGeofencing &manager);
    void showHeader() override;

private:
    SignalingManagerGeofencing &signalingManagerGeofencing;
};
