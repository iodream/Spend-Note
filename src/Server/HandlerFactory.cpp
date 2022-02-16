#include <iostream>

#include "HandlerFactory.h"
#include "libdal/Facade/DbFacade.h"

#include "Handlers/Product/GetProductsHandler.h"
#include "Handlers/Product/AddProductHandler.h"
#include "Handlers/Product/RemoveProductHandler.h"
#include "Handlers/List/RemoveListHandler.h"
#include "Handlers/Income/RemoveIncomeHandler.h"
#include "Handlers/Income/UpdateIncomeHandler.h"
#include "Logger/ScopedLogger.h"

const std::string DB_CONN_STRING =
	"user=test_user host=127.0.0.1 "
	"password=test_pass dbname=SpendAndNote";

HandlerFactory::HandlerFactory()
{


}

Poco::Net::HTTPRequestHandler* HandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& http_req)
{
	SCOPED_LOGGER;
	try{
		return new HTTPRequestHandler{GetCommandHandler(http_req)};
	}
	catch(const std::exception& exception){
		qCritical() << exception.what() << "\n";
	}
	return nullptr;
}

ICommandHandler* HandlerFactory::GetCommandHandler(
		const Poco::Net::HTTPServerRequest& http_req)
{
	SCOPED_LOGGER;
	auto uri = http_req.getURI();
	Params params;
	ICommandHandler* handler = m_resolver.Resolve(uri, http_req.getMethod(), params);


	if (handler) {
		db::IDbFacade::Ptr facade = std::make_unique<db::DbFacade>(DB_CONN_STRING);
		handler->set_facade(std::move(facade));
		handler->set_params(std::move(params));
	}
	return handler;
}
