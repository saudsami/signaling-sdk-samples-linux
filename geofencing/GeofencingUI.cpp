#include "GeofencingUI.h"
#include "../TerminalColors.h"

GeofencingUI::GeofencingUI(SignalingManagerGeofencing &signalingManager)
    : AuthenticationWorkflowUI(signalingManager), signalingManagerGeofencing(signalingManager)
{
  // Additional initialization if needed
}

void GeofencingUI::showHeader()
{
  std::cout << MAGENTA << "\nWelcome to the Signaling Geofencing demo.\n";
}

