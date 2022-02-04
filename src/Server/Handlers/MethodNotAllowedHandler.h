#pragma once

#include <string>
#include <memory>

#include "ICommandHandler.h"

class MethodNotAllowedHandler : public ICommandHandler
{
public:
	MethodNotAllowedHandler();
	virtual ~MethodNotAllowedHandler() override {}

	Net::Response Handle(Net::Request& request) override;
};
