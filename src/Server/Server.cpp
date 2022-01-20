#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/NetException.h"

#include "Server.h"
#include "Utils.h"
#include "Net/Constants.h"
#include "HandlerFactory.h"
#include "SpendNoteServer_Config.h"


void HTTPRequestHandler::handleRequest(HTTPRequest& http_req, HTTPResponse& http_res)
{
	std::cout << "Request from " << http_req.clientAddress() << "\n";

	try {
		if (!m_handler) {
			throw Net::NotFoundError{
				std::string{"No such URI \""}.
				append(http_req.getURI()).
				append("\"")};
		}

		auto request  = ParseRequest(http_req);
		auto response = m_handler->Handle(request);
		SendResponse(response, http_res);
	}
	catch (const Net::ClientError& ex) {
		std::cout << ex.what() << "(URI: " << http_req.getURI() << ")" << "\n";
		SendResponse(FormErrorResponse(ex), http_res);
	}
	catch (const Net::ServerError& ex) {
		std::cout << ex.what() << "(URI: " << http_req.getURI() << ")" << "\n";
		SendResponse(FormErrorResponse(ex), http_res);
	}
	catch (const std::exception& ex) {
		std::cout << "Unhandled exception \"" << ex.what() << "\""
		<< "(URI: " << http_req.getURI() << ")" << "\n";
		SendResponse(FormErrorResponse(), http_res);
	}
	catch (...) {
		std::cout << "Unhandled exception"
		<< "(URI: " << http_req.getURI() << ")" << "\n";
		SendResponse(FormErrorResponse(), http_res);
	}
}

Net::Request HTTPRequestHandler::ParseRequest(HTTPRequest& http_req)
{
	Net::Request request;
	request.method = http_req.getMethod();
	request.content_type = http_req.getContentType();
	if (request.content_type == Net::CONTENT_TYPE_APPLICATION_JSON)
		request.json_payload = ReadJSON(http_req.stream());
	else if (request.content_type == Net::CONTENT_TYPE_PLAIN_TEXT)
		;
	else if (request.content_type == Net::CONTENT_TYPE_EMPTY)
		;
	else
		throw Net::BadRequestError("Unsupported content type");

	try {
		http_req.getCredentials(request.auth_scheme, request.auth_info);
	}  catch (const Poco::Net::NotAuthenticatedException&) {
		;
	}
	return request;
}

QJsonDocument HTTPRequestHandler::ReadJSON(std::istream& is)
{
	std::vector<char> json_doc_raw{
		std::istreambuf_iterator<char>{is},
		std::istreambuf_iterator<char>{}};
	return QJsonDocument::fromJson(
		QByteArray::fromRawData(json_doc_raw.data(), json_doc_raw.size())
	);
}

void HTTPRequestHandler::SendResponse(
	const Net::Response& response,
	HTTPResponse& http_res)
{
	http_res.setChunkedTransferEncoding(true);
	http_res.setContentType(response.content_type);

	if (!response.reason.size()) {
		http_res.setStatusAndReason(response.status);
	}
	else {
		http_res.setReason(response.reason);
		http_res.setStatus(response.status);
	}

	std::ostream& data_stream = http_res.send();

	if (response.content_type == Net::CONTENT_TYPE_APPLICATION_JSON)
		data_stream << response.json_payload.toJson().constData();
	else if (response.content_type == Net::CONTENT_TYPE_PLAIN_TEXT)
		;
	else if (response.content_type == Net::CONTENT_TYPE_EMPTY)
		;
	else
		throw Net::InternalError("Unsupported content type");
}

Net::Response HTTPRequestHandler::FormErrorResponse(const Net::ClientError& ex)
{
	return ::FormErrorResponse(ex.get_status(), ex.what());
}

Net::Response HTTPRequestHandler::FormErrorResponse(const Net::ServerError& ex)
{
	return ::FormErrorResponse(ex.get_status());
}

Net::Response HTTPRequestHandler::FormErrorResponse()
{
	return ::FormErrorResponse(
		Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
}

class HTTPRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
{
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& http_req)
	{
		auto uri = http_req.getURI();
		return new HTTPRequestHandler{m_handler_factory.GetHandler(uri)};
	}

	HandlerFactory m_handler_factory{};
};

class HTTPServer: public Poco::Util::ServerApplication
{
	void initialize(Application& self)
	{
		loadConfiguration();
		ServerApplication::initialize(self);
	}

	int main(const std::vector<std::string>&)
	{
		Poco::UInt16 port = static_cast<Poco::UInt16>(config().getUInt("port", 8080));

		auto* params = new Poco::Net::HTTPServerParams();
		params->setSoftwareVersion(
			std::string{"Spend&NoteServer/"}.
			append(std::string{SpendNoteServer_VERSION_MAJOR}).
			append(std::string{"."}).
			append(std::string{SpendNoteServer_VERSION_MINOR}));

		Poco::Net::HTTPServer srv(new HTTPRequestHandlerFactory, port);
		srv.start();
		std::cout << "HTTP Server started on port " << port << "\n";
		waitForTerminationRequest();
		std::cout << "Stopping HTTP Server..." << "\n";
		srv.stop();

		return Application::EXIT_OK;
	}
};

POCO_SERVER_MAIN(HTTPServer)
