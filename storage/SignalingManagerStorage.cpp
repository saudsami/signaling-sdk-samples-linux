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
    int ttl = 90;
    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->getLock()->setLock(channelName.c_str(), RTM_CHANNEL_TYPE_MESSAGE,
                                       lockName.c_str(), ttl, requestId);

    if (ret != RTM_ERROR_OK)
    {
        printf("setLock failed error is %d reason is %s\n", ret, getErrorReason(ret));
    }
}
