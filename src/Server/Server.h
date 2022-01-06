#pragma once

#include <memory>
#include <exception>

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "Handlers/ICommandHandler.h"
#include "Net/Message.h"
#include "Net/Error.h"

class HTTPRequestHandler: public Poco::Net::HTTPRequestHandler
{
public:
    HTTPRequestHandler(ICommandHandler* handler) : m_handler{handler} {}
private:
	using HTTPResponse = Poco::Net::HTTPServerResponse;
	using HTTPRequest = Poco::Net::HTTPServerRequest;

	void handleRequest(HTTPRequest& http_req, HTTPResponse& http_res);
    QJsonDocument ReadJSON(std::istream& is);
	void SendResponse(const Net::Response& response, HTTPResponse& http_res);
	Net::Request ParseRequest(HTTPRequest& http_req);
	Net::Response FormErrorResponse(const Net::ClientError& ex);
	Net::Response FormErrorResponse(const Net::ServerError& ex);
	Net::Response FormErrorResponse(const std::exception& ex);
private:
    std::unique_ptr<ICommandHandler> m_handler;
};
