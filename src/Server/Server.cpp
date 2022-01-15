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
#include "ClientError.h"
#include "HandlerFactory.h"

void HTTPRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
{
	std::cout << "Request from " << request.clientAddress() << "\n";

	try {
		if (!m_handler)
			throw NotFoundError(std::string{"No such URI \""}.append(request.getURI()).append("\""));

		std::string token_body;

		QJsonDocument json_doc_req;
		auto content_type = request.getContentType();
		if (content_type == std::string{"application/json"})
			json_doc_req = ReadJSON(request.stream());

		auto json_doc_resp = m_handler->Handle(json_doc_req);
		SendJSON(json_doc_resp, response);
	}
	catch (const ClientError& ex) {
		std::cout << ex.what() << "\n";
		SendErrorResponse(ex.get_status(), response);
	}
	catch (const std::exception& ex) {
		std::cout << "Unhandled exception \"" << ex.what() << "\"\n";
		SendErrorResponse(
			Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR,
			response);
	}
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

void HTTPRequestHandler::SendJSON(
		const QJsonDocument& json_doc,
		Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("application/json");

	response.send() << json_doc.toJson().constData();
}

void HTTPRequestHandler::SendErrorResponse(
		Poco::Net::HTTPServerResponse::HTTPStatus status,
		Poco::Net::HTTPServerResponse& response)
{
	response.setChunkedTransferEncoding(true);
	response.setContentType("text/plain; charset=\"UTF-8\"");
	response.setStatusAndReason(status);
	response.send();
}


class HTTPRequestHandlerFactory: public Poco::Net::HTTPRequestHandlerFactory
{
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request)
	{
		auto uri = request.getURI();
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
		params->setSoftwareVersion("Spend&NoteServer/1.0");

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
