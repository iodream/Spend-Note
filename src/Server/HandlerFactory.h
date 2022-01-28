#pragma once

#include <vector>
#include <string>

#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"

#include "HTTPRequestHandler.h"
#include "Handlers/ICommandHandler.h"

class HandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
{
public:
	HandlerFactory() {}
	~HandlerFactory() override {}

	Poco::Net::HTTPRequestHandler* createRequestHandler(
			const Poco::Net::HTTPServerRequest& http_req) override;

private:
	ICommandHandler* GetCommandHandler(const Poco::Net::HTTPServerRequest& http_req);
};
