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

HandlerFactory::HandlerFactory(const Poco::Util::JSONConfiguration& config)
	: m_db_connection_string(m_db_connection_helper.FormConnectionString(config)) {}

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
		db::IDbFacade::Ptr facade = std::make_unique<db::DbFacade>(m_db_connection_string);
		handler->set_facade(std::move(facade));
		handler->set_params(std::move(params));
	}
	return handler;
}
