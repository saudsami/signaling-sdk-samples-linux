#include "EncryptionUI.h"
#include "../TerminalColors.h"

EncryptionUI::EncryptionUI(SignalingManagerEncryption &signalingManager)
    : AuthenticationWorkflowUI(signalingManager), signalingManagerEncryption(signalingManager)
{
  // Additional initialization if needed
}

void EncryptionUI::showHeader()
{
  std::cout << MAGENTA << "\nWelcome to the Signaling Encryption demo.\n";
}

