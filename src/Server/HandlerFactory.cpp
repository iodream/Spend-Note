#include <iostream>

#include "HandlerFactory.h"
#include "libdal/Facade/DbFacade.h"

#include "Handlers/Product/GetProductsHandler.h"
#include "Handlers/Product/AddProductHandler.h"
#include "Handlers/Product/RemoveProductHandler.h"
#include "Handlers/List/RemoveListHandler.h"
#include "Handlers/Income/RemoveIncomeHandler.h"
#include "Handlers/Income/UpdateIncomeHandler.h"

const std::string DB_CONN_STRING =
	"user=test_user host=127.0.0.1 "
	"password=test_pass dbname=SpendAndNote";

HandlerFactory::HandlerFactory()
{

}

Poco::Net::HTTPRequestHandler* HandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& http_req)
{
	try{
		return new HTTPRequestHandler{GetCommandHandler(http_req)};
	}
	catch(const std::exception& exception){
		std::cout << exception.what() << std::endl;
    }
	return nullptr;
}

ICommandHandler* HandlerFactory::GetCommandHandler(
		const Poco::Net::HTTPServerRequest& http_req)
{
	auto uri = http_req.getURI();
	Params params;
	ICommandHandler* handler = m_resolver.Resolve(uri, http_req.getMethod(), params);


	if (handler) {
		IDbFacade::Ptr facade = std::make_unique<DbFacade>(DB_CONN_STRING);
		handler->set_facade(std::move(facade));
		handler->set_params(std::move(params));
	}
//	if (uri == std::string("/product/get_by_list_id"))
//		return new GetProductsHandler(std::move(facade));
//	if (uri == std::string("/product/add"))
//		return new AddProductHandler(std::move(facade));
//	if (uri == std::string("/product/remove"))
//		return new RemoveProductHandler(std::move(facade));
//	if (uri == std::string("/list/get_lists"))
//		return new GetListsHandler(std::move(facade));
//	if (uri == std::string("/list/remove"))
//		return new RemoveListHandler(std::move(facade));
//	if (uri == std::string("/income/remove"))
//		return new RemoveIncomeHandler(std::move(facade));
//	if (uri == std::string("/income/update"))
//		return new UpdateIncomeHandler(std::move(facade));
	return handler;
}
