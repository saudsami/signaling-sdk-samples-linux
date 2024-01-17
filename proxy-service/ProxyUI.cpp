#include "ProxyUI.h"
#include "../TerminalColors.h"

ProxyUI::ProxyUI(SignalingManagerProxy &signalingManager)
    : AuthenticationWorkflowUI(signalingManager), signalingManagerProxy(signalingManager)
{
  // Additional initialization if needed
}

void ProxyUI::showHeader()
{
  std::cout << MAGENTA << "\nWelcome to the Signaling Proxy demo.\n";
}

