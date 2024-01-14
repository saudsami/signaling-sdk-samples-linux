#pragma once

#include "../authentication-workflow/SignalingManagerAuthentication.h"
#include "StreamChannelEventHandler.h"

class SignalingManagerStreamChannel : public SignalingManagerAuthentication
{
public:
    SignalingManagerStreamChannel();
    void joinStreamChannel(std::string channelName);
    void leaveStreamChannel(std::string channelName);
    void joinTopic(std::string topicName);
    void leaveTopic(std::string topicName);
    void subscribeTopic(std::string topicName, std::string user);
    void publishTopicMessage(std::string topic, std::string message);

protected:
    IStreamChannel *streamChannel;
};
