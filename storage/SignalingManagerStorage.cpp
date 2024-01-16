#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SignalingManagerStorage.h"

SignalingManagerStorage::SignalingManagerStorage()
    : SignalingManagerAuthentication()
{
    // Additional initialization
    eventHandler_ = std::unique_ptr<StorageEventHandler>(new StorageEventHandler(this));
}

void SignalingManagerStorage::setLock(std::string lockName)
{
    int ttl = 90;       // The lock expiration time ins seconds, value range is [10,300].
    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getLock()->setLock(channelName.c_str(), channelType,
                                                  lockName.c_str(), ttl, requestId);

    if (ret != RTM_ERROR_OK)
    {
        printf("setLock failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerStorage::acquireLock(std::string lockName)
{
    uint64_t requestId; // Output parameter used to identify and process the result
    bool retry = false;
    int ret = signalingEngine->getLock()->acquireLock(channelName.c_str(), channelType, lockName.c_str(), retry, requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("acquireLock failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}
void SignalingManagerStorage::releaseLock(std::string lockName)
{
    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getLock()->releaseLock(channelName.c_str(), channelType, lockName.c_str(), requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("releaseLock failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}
void SignalingManagerStorage::removeLock(std::string lockName)
{
    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getLock()->removeLock(channelName.c_str(), channelType, lockName.c_str(), requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("removeLock failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}
void SignalingManagerStorage::getLocks(std::string channelName)
{
    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getLock()->getLocks(channelName.c_str(), channelType, requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("getLocks failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerStorage::getChannelMetadata(std::string channelName)
{
    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getStorage()->getChannelMetadata(channelName.c_str(), channelType, requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("getChannelMetadata failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerStorage::getUserMetadata(std::string userId)
{
    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getStorage()->getUserMetadata(userId.c_str(), requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("getUserMetadata failed error: %d reason: %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerStorage::setChannelMetadata(std::string key, std::string value, int64_t revision, std::string lockName)
{
    std::cout << "\n"
              << channelName << " " << key << " " << value << " "
              << revision << " " << lockName;
    IMetadata *metadata = signalingEngine->getStorage()->createMetadata();
    MetadataOptions options;
    MetadataItem item;
    item.key = key.c_str();
    item.value = value.c_str();
    item.revision = revision;
    metadata->setMetadataItem(item);
    metadata->setMajorRevision(-1);

    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getStorage()->setChannelMetadata(
        channelName.c_str(), channelType,
        metadata, options,
        lockName.c_str(), requestId);
}

void SignalingManagerStorage::updateChannelMetadata(std::string key, std::string value, int64_t revision, std::string lockName)
{
    IMetadata *metadata = signalingEngine->getStorage()->createMetadata();
    MetadataOptions options;
    MetadataItem item;
    item.key = key.c_str();
    item.value = value.c_str();
    item.revision = revision;
    metadata->setMetadataItem(item);

    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getStorage()->updateChannelMetadata(
        channelName.c_str(), channelType,
        metadata, options,
        lockName.c_str(), requestId);
}

void SignalingManagerStorage::removeChannelMetadata(std::string key)
{
    std::string lockName = "";
    IMetadata *metadata = signalingEngine->getStorage()->createMetadata();
    MetadataOptions options;
    MetadataItem item;
    item.key = key.c_str();
    metadata->setMetadataItem(item);

    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getStorage()->removeChannelMetadata(
        channelName.c_str(), channelType,
        metadata, options,
        lockName.c_str(), requestId);
}

void SignalingManagerStorage::setUserMetadata(std::string key, std::string value, int64_t revision)
{
    IMetadata *metadata = signalingEngine->getStorage()->createMetadata();
    MetadataOptions options;
    MetadataItem item;
    item.key = key.c_str();
    item.value = value.c_str();
    item.revision = revision;
    item.authorUserId = uid.c_str();
    metadata->setMetadataItem(item);

    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getStorage()->setUserMetadata(
        uid.c_str(), metadata, options, requestId);
}

void SignalingManagerStorage::removeUserMetadata(std::string key)
{
    IMetadata *metadata = signalingEngine->getStorage()->createMetadata();
    MetadataOptions options;
    MetadataItem item;
    item.key = key.c_str();
    item.revision = -1;
    metadata->setMetadataItem(item);

    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getStorage()->removeUserMetadata(
        uid.c_str(), metadata, options, requestId);
}

void SignalingManagerStorage::subscribeUserMetadata(std::string userId)
{
    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getStorage()->subscribeUserMetadata(userId.c_str(), requestId);
    if (ret != RTM_ERROR_OK)
    {
        printf("subscribeUserMetadata failed error is %d reason is %s\n", ret, getErrorReason(ret));
    }
}

void SignalingManagerStorage::unsubscribeUserMetadata(std::string userId)
{
    int ret = signalingEngine->getStorage()->unsubscribeUserMetadata(userId.c_str());
    if (ret != RTM_ERROR_OK)
    {
        printf("unsubscribeUserMetadata failed error is %d reason is %s\n", ret, getErrorReason(ret));
    }
}