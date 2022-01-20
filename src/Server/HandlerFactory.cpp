#include "HandlerFactory.h"
#include "Handlers/LoginHandler.h"
#include "Handlers/EchoHandler.h"
#include "Handlers/FakeGetListsHandler.h"

ICommandHandler* HandlerFactory::GetHandler(std::string uri)
{
	if (uri == std::string("/echo"))
		return new EchoHandler;
	if (uri == std::string("/login"))
		return new LoginHandler;
	if (uri == std::string("/fake_get_lists"))
		return new FakeGetListsHandler;
	return nullptr;
}
