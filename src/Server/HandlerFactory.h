#pragma once

#include <vector>
#include <string>

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Util/JSONConfiguration.h"

#include "HTTPRequestHandler.h"
#include "Resolvers/RootResolver.h"

class HandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
	HandlerFactory();
	~HandlerFactory() override {}

	Poco::Net::HTTPRequestHandler* createRequestHandler(
		const Poco::Net::HTTPServerRequest& http_req) override;

	std::string_view GetPathSegment(std::string& path, std::string::size_type pos);

private:
	ICommandHandler* GetCommandHandler(const Poco::Net::HTTPServerRequest& http_req);

	std::string FormConnectionString() const;

	const std::string m_db_connection_string;

	RootResolver m_resolver;
};
