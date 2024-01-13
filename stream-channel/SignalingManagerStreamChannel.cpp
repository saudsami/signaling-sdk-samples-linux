#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SignalingManagerStreamChannel.h"

SignalingManagerStreamChannel::SignalingManagerStreamChannel()
    : SignalingManagerAuthentication()
{
    // Additional initialization
    eventHandler_ = std::unique_ptr<StreamChannelEventHandler>(new StreamChannelEventHandler(this));
}

void SignalingManagerStreamChannel::joinStreamChannel(std::string channelName)
{
    // Create a stream channel
    streamChannel = signalingEngine->createStreamChannel(channelName.c_str());
    if (streamChannel == nullptr)
    {
        printf("create stream channel failed\n");
        return;
    }
    else
    {
        printf("create stream channel success\n");
    }

    // Join the stream channel
    std::string rtcToken = fetchRTCToken(channelName); // config["rtcToken"];
    JoinChannelOptions options;
    options.token = rtcToken.c_str();
    options.withLock = true;
    options.withMetadata = true;
    options.withPresence = true;

    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = streamChannel->join(options, requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("join channel failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerStreamChannel::leaveStreamChannel(std::string channelName)
{
    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = streamChannel->leave(requestId);

    if (ret != RTM_ERROR_OK)
    {
        printf("leave rtm channel failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerStreamChannel::joinTopic(std::string topicName)
{

    JoinTopicOptions topicOptions;
    topicOptions.qos = RTM_MESSAGE_QOS_ORDERED;
    uint64_t requestId; // Output parameter used to identify and process the result

    int ret = streamChannel->joinTopic(topicName.c_str(), topicOptions, requestId);

    if (ret != RTM_ERROR_OK)
    {
        printf("JoinTopic failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerStreamChannel::leaveTopic(std::string topicName)
{
    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = streamChannel->leaveTopic(topicName.c_str(), requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("leaveTopic failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerStreamChannel::subscribeTopic(std::string topicName)
{
    uint64_t requestId; // Output parameter used to identify and process the result
    TopicOptions topicOptions;
    /*
    const char *user1 = "1";
    const char *user2 = "2";

    const char *userList[2] = {user1, user2};
    topicOptions.userCount = 2;
    topicOptions.users = userList;
*/
    int ret = streamChannel->subscribeTopic(topicName.c_str(), topicOptions, requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("subscribeTopic failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerStreamChannel::publishTopicMessage(std::string topic, std::string message)
{
    const TopicMessageOptions topicMessageOptions;
   
    int ret = streamChannel->publishTopicMessage(topic.c_str(), message.c_str(),
                                  message.length(), topicMessageOptions);
    if (ret != RTM_ERROR_OK)
    {
        printf("publishTopicMessage failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }                                  
}