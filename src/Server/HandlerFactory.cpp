#include "HandlerFactory.h"
#include "Handlers/LoginHandler.h"
#include "Handlers/EchoHandler.h"
#include "Handlers/SignupHandler.h"
#include "Handlers/Income/GetIncomesHandler.h"
#include "Handlers/Product/GetProductsHandler.h"
#include "Handlers/Product/AddProductHandler.h"
#include "Handlers/Product/RemoveProductHandler.h"
#include "Handlers/List/GetListsHandler.h"
#include "Handlers/List/RemoveListHandler.h"
#include "Handlers/Income/AddIncomeHandler.h"
#include "Handlers/Income/RemoveIncomeHandler.h"
#include "Handlers/Income/UpdateIncomeHandler.h"
#include "Handlers/Product/UpdateProductHandler.h"
#include "Handlers/List/UpdateListHandler.h"

#include "libdal/Facade/DbFacade.h"

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
	if (uri == std::string("/signup"))
		return new SignupHandler(std::move(facade));
	if (uri == std::string("/income/get"))
		return new GetIncomesHandler(std::move(facade));
	if (uri == std::string("/product/get_by_list_id"))
		return new GetProductsHandler(std::move(facade));
	if (uri == std::string("/product/add"))
		return new AddProductHandler(std::move(facade));
	if (uri == std::string("/product/remove"))
		return new RemoveProductHandler(std::move(facade));
	if (uri == std::string("/list/get_lists"))
		return new GetListsHandler(std::move(facade));
	if (uri == std::string("/income/add"))
		return new AddIncomeHandler(std::move(facade));
	if (uri == std::string("/list/remove"))
		return new RemoveListHandler(std::move(facade));
	if (uri == std::string("/income/remove"))
		return new RemoveIncomeHandler(std::move(facade));
	if (uri == std::string("/income/update"))
		return new UpdateIncomeHandler(std::move(facade));

	return nullptr;
}
