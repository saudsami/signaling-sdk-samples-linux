#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SignalingManagerEncryption.h"

SignalingManagerEncryption::SignalingManagerEncryption()
    : SignalingManagerAuthentication()
{
    // Additional initialization
    eventHandler_ = std::unique_ptr<EncryptionEventHandler>(new EncryptionEventHandler(this));
}

