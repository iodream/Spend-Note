#include <iostream>

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/NetException.h"

#include "HTTPRequestHandler.h"
#include "Utils.h"
#include "Logger/ScopedLogger.h"

void HTTPRequestHandler::handleRequest(HTTPRequest& http_req, HTTPResponse& http_res)
{
	SCOPED_LOGGER;
	qDebug() << "Request from " <<
		QString::fromStdString(http_req.clientAddress().toString()) << "\n";

	try {
		if (!m_command_handler) {
			throw NotFoundError{
				std::string{"No such URI \""}.
				append(http_req.getURI()).
				append("\"")};
		}

		auto request  = ParseRequest(http_req);
		auto response = m_command_handler->Handle(request);
		SendResponse(response, http_res);
	}
	catch (const ClientError& ex) {
		qWarning() << ex.what() << "(URI: " <<
		QString::fromStdString(http_req.getURI()) << ")" << "\n";
		SendResponse(FormErrorResponse(ex), http_res);
	}
	catch (const ServerError& ex) {
		qWarning() << ex.what() << "(URI: " <<
			QString::fromStdString(http_req.getURI()) << ")" << "\n";
		SendResponse(FormErrorResponse(ex), http_res);
	}
	catch (const std::exception& ex) {
		qCritical() << "Unhandled exception \"" << ex.what() << "\""
			<< "(URI: " << QString::fromStdString(http_req.getURI()) << ")" << "\n";
		SendResponse(FormErrorResponse(), http_res);
	}
	catch (...) {
		qCritical() << "Unhandled exception"
			<< "(URI: " << QString::fromStdString(http_req.getURI()) << ")" << "\n";
		SendResponse(FormErrorResponse(), http_res);
	}
}

Net::Request HTTPRequestHandler::ParseRequest(HTTPRequest& http_req)
{
	SCOPED_LOGGER;
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
		throw BadRequestError("Unsupported content type");

	try {
		http_req.getCredentials(request.auth_scheme, request.auth_info);
	}  catch (const Poco::Net::NotAuthenticatedException&) {
		;
	}
	return request;
}

QJsonDocument HTTPRequestHandler::ReadJSON(std::istream& is)
{
	SCOPED_LOGGER;
	std::string json_doc_raw(std::istreambuf_iterator<char>(is), {});

	return QJsonDocument::fromJson(
		QByteArray::fromRawData(json_doc_raw.c_str(), json_doc_raw.size())
	);
}

void HTTPRequestHandler::SendResponse(
	const Net::Response& response,
	HTTPResponse& http_res)
{
	SCOPED_LOGGER;
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
		throw InternalError("Unsupported content type");
}

Net::Response HTTPRequestHandler::FormErrorResponse(const ClientError& ex)
{
	SCOPED_LOGGER;
	return ::FormErrorResponse(ex.get_status(), ex.what());
}

Net::Response HTTPRequestHandler::FormErrorResponse(const ServerError& ex)
{
	SCOPED_LOGGER;
	return ::FormErrorResponse(ex.get_status());
}

Net::Response HTTPRequestHandler::FormErrorResponse()
{
	SCOPED_LOGGER;
	return ::FormErrorResponse(
		Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
}
