#include "StreamChannelEventHandler.h"
#include "SignalingManagerStreamChannel.h"

StreamChannelEventHandler::StreamChannelEventHandler(SignalingManager *manager)
    : AuthenticationEventHandler(manager)
{
  signalingManagerStreamChannel = static_cast<SignalingManagerStreamChannel *>(signalingManager);
}

void StreamChannelEventHandler::onJoinResult(const uint64_t requestId, const char *channelName, const char *userId, RTM_ERROR_CODE errorCode)
{
  if (errorCode != RTM_ERROR_OK)
  {
    printf("Join stream channel failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
  }
  else
  {
    printf("Join stream channel %s success\n", channelName);
  }
}

void StreamChannelEventHandler::onLeaveResult(const uint64_t requestId, const char *channelName, const char *userId, RTM_ERROR_CODE errorCode)
{
  if (errorCode != RTM_ERROR_OK)
  {
    printf("Leave stream channel failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
  }
  else
  {
    printf("Left the stream channel: %s \n", channelName);
  }
}

void StreamChannelEventHandler::onJoinTopicResult(const uint64_t requestId, const char *channelName, const char *userId, const char *topic, const char *meta, RTM_ERROR_CODE errorCode)
{
  if (errorCode != RTM_ERROR_OK)
  {
    printf("joinTopic failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
  }
  else
  {
    printf("joinTopic success\n");
  }
}

void StreamChannelEventHandler::onSubscribeTopicResult(const uint64_t requestId, const char *channelName, const char *userId, const char *topic, UserList succeedUsers, UserList failedUsers, RTM_ERROR_CODE errorCode)
{
  if (errorCode != RTM_ERROR_OK)
  {
    printf("subscribeTopic failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
  }
  else
  {
    printf("subscribeTopic success\n");
  }
}

void StreamChannelEventHandler::onLeaveTopicResult(const uint64_t requestId, const char *channelName, const char *userId, const char *topic, const char *meta, RTM_ERROR_CODE errorCode)
{
  if (errorCode != RTM_ERROR_OK)
  {
    printf("leaveTopic failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
  }
  else
  {
    printf("leaveTopic success\n");
  }
}

void StreamChannelEventHandler::onTopicEvent(const TopicEvent &event)
{
  // Check the value of event.type and inform the user accordingly.
  switch (event.type)
  {
  case RTM_TOPIC_EVENT_TYPE_SNAPSHOT:
    // Topic snapshot information when joining the channel
    cbPrint("Topic snapshot event.");
    break;

  case RTM_TOPIC_EVENT_TYPE_REMOTE_JOIN_TOPIC:
    // A remote user joined the topic
    cbPrint("Remote user joined: %s", event.publisher);
    
    break;

  case RTM_TOPIC_EVENT_TYPE_REMOTE_LEAVE_TOPIC:
    // A remote user left the topic
    cbPrint("Remote user left: %s", event.publisher);
    break;

  default:
    std::cout << "Unknown topic event type: " << event.type << std::endl;
    break;
  }
}