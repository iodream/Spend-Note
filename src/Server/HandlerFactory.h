#pragma once

#include <vector>
#include <string>

#include "Handlers/ICommandHandler.h"

class HandlerFactory
{
public:
	ICommandHandler* GetHandler(std::string uri);
};
