#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SignalingManagerProxy.h"

SignalingManagerProxy::SignalingManagerProxy()
    : SignalingManagerAuthentication()
{
    // Additional initialization
    eventHandler_ = std::unique_ptr<AuthenticationEventHandler>(new AuthenticationEventHandler(this));
}

void SignalingManagerProxy::loginWithToken(std::string userId)
{
    std::cout << "Fetching token from the server..." << std::endl;
    token = fetchRTMToken(userId);
    uid = userId;

    RtmConfig rtmConfig;
    rtmConfig.appId = appId.c_str();
    rtmConfig.userId = uid.c_str();
    rtmConfig.presenceTimeout = config["presenceTimeout"];
    rtmConfig.eventHandler = eventHandler_.get();

    std::cout << "Setting proxy config\n";
    RtmProxyConfig proxyConfig;
    proxyConfig.account = "<account>"; // 	Proxy login account
    proxyConfig.password = "<password>"; // 	Proxy login password
    proxyConfig.port = 1234; // Proxy listening port
    proxyConfig.proxyType = RTM_PROXY_TYPE_HTTP; // Proxy type
    proxyConfig.server = "<proxy server>"; // Proxy server domain name or IP address
    rtmConfig.proxyConfig = proxyConfig;

    // Initialize the signalingEngine
    int ret = signalingEngine->initialize(rtmConfig);
    std::cout << "Initialize returned: " << ret << std::endl;
    if (ret)
    {
        std::cout << "Error initializing Signaling service: " << ret << std::endl;
        exit(0);
    }

    // Log in using the token
    ret = signalingEngine->login(token.c_str());
    std::cout << "Login returned: " << ret << std::endl;
    if (ret)
    {
        std::cout << "Login failed: " << ret << std::endl;
        exit(0);
    }
}
