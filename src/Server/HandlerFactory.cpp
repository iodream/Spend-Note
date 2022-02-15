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

HandlerFactory::HandlerFactory() : m_db_connection_string(FormConnectionString()) {}

std::string HandlerFactory::FormConnectionString() const
{
	const std::string config_filename =
		std::string(std::filesystem::current_path())
		+ std::string("/Config.json");

	Poco::Util::JSONConfiguration m_json_configuration(config_filename);

	return "user=" +
		m_json_configuration.getString("user") +
		" host=" +
		m_json_configuration.getString("host") +
		" password=" +
		m_json_configuration.getString("password") +
		" dbname=" +
		m_json_configuration.getString("dbname");
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
		db::IDbFacade::Ptr facade = std::make_unique<db::DbFacade>(m_db_connection_string);
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
