#include "StorageEventHandler.h"
#include "SignalingManagerStorage.h"

StorageEventHandler::StorageEventHandler(SignalingManager *manager)
    : AuthenticationEventHandler(manager)
{
    signalingManagerStorage = static_cast<SignalingManagerStorage *>(signalingManager);
}

std::string StorageEventHandler::getLockEventDescription(RTM_LOCK_EVENT_TYPE eventType)
{
    static const std::unordered_map<RTM_LOCK_EVENT_TYPE, std::string> eventDescriptions = {
        {RTM_LOCK_EVENT_TYPE_SNAPSHOT, "Snapshot information of Lock when joining the channel."},
        {RTM_LOCK_EVENT_TYPE_LOCK_SET, "Lock has been set."},
        {RTM_LOCK_EVENT_TYPE_LOCK_REMOVED, "Lock has been deleted."},
        {RTM_LOCK_EVENT_TYPE_LOCK_ACQUIRED, "Lock has been obtained."},
        {RTM_LOCK_EVENT_TYPE_LOCK_RELEASED, "Lock has been released."},
        {RTM_LOCK_EVENT_TYPE_LOCK_EXPIRED, "Lock has expired."}};

    auto it = eventDescriptions.find(eventType);
    if (it != eventDescriptions.end())
    {
        return it->second;
    }
    else
    {
        return "Unknown Lock Event Type.";
    }
}

std::string StorageEventHandler::getStorageEventDescription(RTM_STORAGE_EVENT_TYPE eventType)
{
    static const std::unordered_map<RTM_STORAGE_EVENT_TYPE, std::string> eventDescriptions = {
        {RTM_STORAGE_EVENT_TYPE_SNAPSHOT, "RTM_STORAGE_EVENT_TYPE_SNAPSHOT"},
        {RTM_STORAGE_EVENT_TYPE_REMOVE, "RTM_STORAGE_EVENT_TYPE_REMOVE"},
        {RTM_STORAGE_EVENT_TYPE_SET, "RTM_STORAGE_EVENT_TYPE_SET"},
        {RTM_STORAGE_EVENT_TYPE_UPDATE, "RTM_STORAGE_EVENT_TYPE_UPDATE"}};
        

    auto it = eventDescriptions.find(eventType);
    if (it != eventDescriptions.end())
    {
        return it->second;
    }
    else
    {
        return "Unknown Storage Event Type.";
    }
}


void StorageEventHandler::onStorageEvent(const StorageEvent &event)
{
    cbPrint(("Lock event: " + getStorageEventDescription(event.eventType)).c_str());
}

void StorageEventHandler::onLockEvent(const LockEvent &event)
{
    cbPrint(("Lock event: " + getLockEventDescription(event.eventType)).c_str());
}

void StorageEventHandler::onSetLockResult(const uint64_t requestId,
                                          const char *channelName, RTM_CHANNEL_TYPE channelType,
                                          const char *lockName, RTM_ERROR_CODE errorCode)
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("setLock failed error: %d reason: %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("setLock success\n");
    }
}

void StorageEventHandler::onAcquireLockResult(const uint64_t requestId, const char *channelName, RTM_CHANNEL_TYPE channelType, const char *lockName, RTM_ERROR_CODE errorCode, const char *errorDetails)
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("acquireLock failed error is %d reason is %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("acquireLock success\n");
    }
}

void StorageEventHandler::onReleaseLockResult(const uint64_t requestId, const char *channelName, RTM_CHANNEL_TYPE channelType, const char *lockName, RTM_ERROR_CODE errorCode)
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("releaseLock failed error is %d reason is %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("releaseLock success\n");
    }
}

void StorageEventHandler::onGetLocksResult(const uint64_t requestId, const char *channelName, RTM_CHANNEL_TYPE channelType, const LockDetail *lockDetailList, const size_t count, RTM_ERROR_CODE errorCode)
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("getLock failed error is %d reason is %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("getLock success\n");
        for (int i = 0; i < count; i++)
        {
            printf("lock: %s owner: %s ttl: %d\n", lockDetailList[i].lockName, lockDetailList[i].owner, lockDetailList[i].ttl);
        }
    }
}

void StorageEventHandler::onRemoveLockResult(const uint64_t requestId, const char *channelName, RTM_CHANNEL_TYPE channelType, const char *lockName, RTM_ERROR_CODE errorCode)
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("removeLock failed error is %d reason is %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("removeLock success\n");
    }
}

void StorageEventHandler::onGetChannelMetadataResult(const uint64_t requestId, const char *channelName, RTM_CHANNEL_TYPE channelType, const IMetadata &data, RTM_ERROR_CODE errorCode) 
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("getChannelMetadata failed error is %d reason is %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("getChannelMetadata success\n");
        const MetadataItem *items;
        size_t size;
        data.getMetadataItems(&items, &size);
        for (int i = 0; i < size; i++)
        {
            printf("key: %s value: %s revison: %ld\n", items[i].key, items[i].value, items[i].revision);
        }
    }
}

void StorageEventHandler::onGetUserMetadataResult(const uint64_t requestId, const char *userId, const IMetadata &data, RTM_ERROR_CODE errorCode) 
{
    if (errorCode != RTM_ERROR_OK)
    {
        printf("getUserMetadata failed error is %d reason is %s\n", errorCode, getErrorReason(errorCode));
    }
    else
    {
        printf("getUserMetadata success user id: %s\n", userId);
        const MetadataItem *items;
        size_t size;
        data.getMetadataItems(&items, &size);
        for (int i = 0; i < size; i++)
        {
            printf("key: %s value: %s revison: %ld\n", items[i].key, items[i].value, items[i].revision);
        }
    }
}

