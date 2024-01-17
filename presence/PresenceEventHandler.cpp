#include "PresenceEventHandler.h"
#include "SignalingManagerPresence.h"

PresenceEventHandler::PresenceEventHandler(SignalingManager *manager)
    : AuthenticationEventHandler(manager)
{
    signalingManagerPresence = static_cast<SignalingManagerPresence *>(signalingManager);
}

void PresenceEventHandler::onGetOnlineUsersResult(const uint64_t requestId,
                                                  const UserState *userStateList, const size_t count,
                                                  const char *nextPage, RTM_ERROR_CODE errorCode)
{

    if (errorCode != RTM_ERROR_OK)
    {
        printf("getOnlineUsers failed error is %d reason is %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("List of users in the channel:\n");
        for (int i = 0; i < count; i++)
        {
            printf("user: %s\n", userStateList[i].userId);
            for (int j = 0; j < userStateList[i].statesCount; j++)
            {
                printf("key: %s value: %s\n", userStateList[i].states[j].key, userStateList[i].states[j].value);
            }
        }
    }
}

void PresenceEventHandler::onGetUserChannelsResult(const uint64_t requestId, const ChannelInfo *channels, const size_t count, RTM_ERROR_CODE errorCode)
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("getUserChannels failed error: %d, reason: %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("User is in the following channels:\n");
        for (int i = 0; i < count; i++)
        {
            printf("channel: %s channel type: %d\n", channels[i].channelName, channels[i].channelType);
        }
    }
}

void PresenceEventHandler::onPresenceSetStateResult(const uint64_t requestId, RTM_ERROR_CODE errorCode)
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("SetState failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("SetState success\n");
    }
}

void PresenceEventHandler::onPresenceGetStateResult(const uint64_t requestId, const UserState &state, RTM_ERROR_CODE errorCode)
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("GetState failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("GetState user id: %s success\n", state.userId);
        for (int i = 0; i < state.statesCount; i++)
        {
            printf("key: %s, value: %s\n", state.states[i].key, state.states[i].value);
        }
    }
}

void PresenceEventHandler::onPresenceRemoveStateResult(const uint64_t requestId, RTM_ERROR_CODE errorCode)
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("RemoveState failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("RemoveState success\n");
    }
}