#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "SignalingManagerStorage.h"

SignalingManagerStorage::SignalingManagerStorage()
    : SignalingManagerAuthentication()
{
    // Additional initialization
    eventHandler_ = std::unique_ptr<StorageEventHandler>(new StorageEventHandler(this));
}

void SignalingManagerStorage::setLock(std::string locklName)
{
    uint64_t requestId; // Output parameter used to identify and process the result
    int ret = signalingEngine->setLock(channelName, RTM_CHANNEL_TYPE channelType,
                                       lockName.c_str(), uint32_t ttl, uint64_t & requestId);

    if (ret != RTM_ERROR_OK)
    {
        printf("setLock failed error is %d reason is %s\n", ret, getErrorReason(ret));
    }
}
