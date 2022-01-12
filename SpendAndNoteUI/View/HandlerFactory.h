#pragma once

#include <string>

#include "Handlers/IHandler.h"

class HandlerFactory
{
public:
    IHandler* FactoryMethod(std::string);
};
