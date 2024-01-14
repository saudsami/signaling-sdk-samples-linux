#pragma once

#include "../authentication-workflow/SignalingManagerAuthentication.h"
#include "StorageEventHandler.h"

class SignalingManagerStorage : public SignalingManagerAuthentication
{
public:
    SignalingManagerStorage();
    void setLock(std::string locklName);
    
private:
};
