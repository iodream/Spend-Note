#pragma once

#include "Net/Message.h"

class ICommandHandler
{
public:
    ICommandHandler() {}
    virtual ~ICommandHandler() {}

	virtual Net::Response Handle(Net::Request& request) = 0;
};
