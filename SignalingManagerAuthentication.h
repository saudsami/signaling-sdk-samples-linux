#pragma once

#include "SignalingManager.h"

class SignalingManagerAuthentication : public SignalingManager {
public:
    
    // Specific methods for DemoExample1
    std::string fetchToken(int userId);
};