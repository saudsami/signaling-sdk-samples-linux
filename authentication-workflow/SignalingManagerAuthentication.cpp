#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SignalingManagerAuthentication.h"

SignalingManagerAuthentication::SignalingManagerAuthentication()
    : SignalingManager()
{
    // Additional initialization
    eventHandler_ = std::unique_ptr<AuthenticationEventHandler>(new AuthenticationEventHandler(this));
    tokenExpiryTime = config["tokenExpiryTime"];
    serverUrl = config["serverUrl"];
}

// Callback function to handle the received data
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output)
{
    size_t totalSize = size * nmemb;
    output->append(static_cast<char *>(contents), totalSize);
    return totalSize;
}

std::string SignalingManagerAuthentication::fetchToken(std::string url)
{
    // Initialize cURL
    CURL *curl = curl_easy_init();

    if (curl)
    {
        // Set the URL for the GET request
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Response data will be stored in this string
        std::string responseData;

        // Set the callback function to handle the received data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

        // Perform the GET request
        CURLcode res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK)
        {
            std::cerr << "Failed to fetch token: " << curl_easy_strerror(res) << std::endl;
        }
        else
        {
            // Parse the JSON response
            try
            {
                json responseJson = json::parse(responseData);

                // Extract the token value
                std::string token;
                if (url.find("rtm") != std::string::npos)
                {
                    token = responseJson["rtmToken"];
                }
                else
                {
                    token = responseJson["rtcToken"];
                }

                // Cleanup and return the token
                curl_easy_cleanup(curl);
                return token;
            }
            catch (const std::exception &e)
            {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
            }
        }

        // Cleanup in case of error
        curl_easy_cleanup(curl);
    }
    else
    {
        std::cerr << "cURL initialization failed." << std::endl;
    }

    return ""; // Return an empty string in case of error
}

std::string SignalingManagerAuthentication::fetchRTMToken(std::string userId)
{
    // Build the URL with the userId
    std::string url = serverUrl + "/rtm/" + userId + "/?expiry=" + std::to_string(tokenExpiryTime);
    return fetchToken(url);
}

std::string SignalingManagerAuthentication::fetchRTCToken(std::string channelName)
{
    // Build the URL with the channelName
    int role = 1;
    std::string url = serverUrl + "/rtc/" + channelName + "/" + std::to_string(role) + "/uid/" + uid + "/?expiry=" + std::to_string(tokenExpiryTime);
    return fetchToken(url);
}

void SignalingManagerAuthentication::loginWithToken(std::string userId)
{
    std::cout << "Fetching token from the server..." << std::endl;
    token = fetchRTMToken(userId);
    uid = userId;

    RtmConfig rtmConfig;
    rtmConfig.appId = appId.c_str();
    rtmConfig.userId = uid.c_str();
    rtmConfig.presenceTimeout = config["presenceTimeout"];
    rtmConfig.eventHandler = eventHandler_.get();

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

int SignalingManagerAuthentication::renewToken()
{
    std::cout << "Fetching token to renew expiring token..." << std::endl;
    token = fetchRTMToken(uid);
    return signalingEngine->renewToken(token.c_str());
}