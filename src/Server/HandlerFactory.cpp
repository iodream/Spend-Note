#include "HandlerFactory.h"
#include "Handlers/LoginHandler.h"
#include "Handlers/EchoHandler.h"
#include "Handlers/GetListsHandler.h"
#include "Handlers/GetProductsHandler.h"

#include "../libdal/Facade/DbFacade.h"

const std::string DB_CONN_STRING =
	"user=test_user host=127.0.0.1 "
	"password=test_pass dbname=SpendAndNote";

ICommandHandler* HandlerFactory::GetHandler(std::string uri)
{
	IDbFacade::Ptr facade = std::make_unique<DbFacade>(DB_CONN_STRING);

	if (uri == std::string("/echo"))
		return new EchoHandler(std::move(facade));
	if (uri == std::string("/login"))
		return new LoginHandler(std::move(facade));
	if (uri == std::string("/get_lists"))
		return new GetListsHandler(std::move(facade));
	if (uri == std::string("/get_products"))
		return new GetProductsHandler(std::move(facade));
	return nullptr;
}
