#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SignalingManagerAuthentication.h"


// Callback function to handle the received data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::string SignalingManagerAuthentication::fetchToken(int userId) {
    // Build the URL with the userId
    std::string url = "https://agora-token-server-5rci.onrender.com/rtm/" 
        + std::to_string(userId) + "/?expiry=76400";

    // Initialize cURL
    CURL* curl = curl_easy_init();
    
    if (curl) {
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
        if (res != CURLE_OK) {
            std::cerr << "Failed to fetch token: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Parse the JSON response
            try {
                json responseJson = json::parse(responseData);

                // Extract the rtmToken value
                std::string rtmToken = responseJson["rtmToken"];
                
                // Cleanup and return the token
                curl_easy_cleanup(curl);
                return rtmToken;
            } catch (const std::exception& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
            }
        }

        // Cleanup in case of error
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "cURL initialization failed." << std::endl;
    }

    return "";  // Return an empty string in case of error
}