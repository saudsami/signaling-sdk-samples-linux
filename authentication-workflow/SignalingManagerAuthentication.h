#pragma once

#include "../SignalingManager.h"

class SignalingManagerAuthentication : public SignalingManager {
public:
    // Implement virtual methods from SignalingManager
    void init() override;
    void login() override;
    void logout() override;
    void subscribeChannel(const std::string& channel) override;
    void unsubscribeChannel(const std::string& channel) override;
    void publishMessage(const std::string& channel, const std::string& message) override;

    // Specific methods for DemoExample1
    // ...
};