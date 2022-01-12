#include "HandlerFactory.h"
#include "Handlers/LoginHandler.h"

IHandler* HandlerFactory::FactoryMethod(std::string handleType)
{
    if(handleType == "login")
    {
        return new LoginHandler;
    }
    else
    {
        return nullptr;
    }
}

