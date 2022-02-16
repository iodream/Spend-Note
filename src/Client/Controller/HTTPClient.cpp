#include <sstream>
#include <QJsonObject>
#include <QMessageBox>

#include <Poco/URI.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Message.h>

#include "Controller.h"
#include "Exception.h"
#include "HTTPClient.h"

void HTTPClient::set_token(const std::string& str_token)
{
    m_token = str_token;
}

void HTTPClient::set_auth_scheme(const std::string& str_auth_scheme)
{
    m_auth_scheme = str_auth_scheme;
}

void HTTPClient::ReleaseToken()
{
	set_token("");
	set_auth_scheme("");
}

void HTTPClient::SendRequest(
	Poco::Net::HTTPRequest& request,
	Poco::Net::HTTPClientSession& session,
	const Net::Request& net_request)
{
    AddCredentials(request);
    request.setContentType(net_request.content_type);

		if (net_request.content_type == Net::CONTENT_TYPE_APPLICATION_JSON)
		{
			QByteArray byte_array = net_request.json_payload.toJson();
			request.setContentLength(byte_array.size());

			std::ostream& out_stream = session.sendRequest(request);
			out_stream << net_request.json_payload.toJson().constData();
		}
		else if (
			net_request.content_type == Net::CONTENT_TYPE_PLAIN_TEXT ||
			net_request.content_type == Net::CONTENT_TYPE_EMPTY)
		{
			session.sendRequest(request);
		}
		else
		{
			throw Exception("Unsupported content type");
		}
}

Net::Response HTTPClient::FormResponse(
    const Poco::Net::HTTPResponse& response,
	std::istream& received_stream)
{
    Net::Response net_response;
    net_response.content_type = response.getContentType();
    net_response.status = response.getStatus();
    net_response.reason = response.getReason();
    std::stringstream string_stream;
    Poco::StreamCopier::copyStream(received_stream, string_stream);
    if (net_response.content_type == Net::CONTENT_TYPE_APPLICATION_JSON)
    {
        QByteArray br = QString::fromStdString(string_stream.str()).toUtf8();
        QJsonDocument json_doc = QJsonDocument::fromJson(br);
		net_response.json_payload = json_doc;
    }
	else if (
		net_response.content_type != Net::CONTENT_TYPE_PLAIN_TEXT &&
		net_response.content_type != Net::CONTENT_TYPE_EMPTY)
    {
		throw Exception("Unsupported content type");
    }
    return net_response;
}

Net::Response HTTPClient::Request(const Net::Request& net_request)
{
    Poco::URI uri(net_request.uri);
    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    std::string path(uri.getPathAndQuery());
    Poco::Net::HTTPRequest request(net_request.method, path, Poco::Net::HTTPMessage::HTTP_1_1);

	bool Retry = false;
	do
	{
		try{
			SendRequest(request, session, net_request);
		}
		catch(const Poco::Exception& exc)
		{
			qCritical() << "Can't send request: " << exc.what();
			if(Controller::AskUser(QString("Retry?"),
								   QString("No connection to server. Retry?")))
			{
				Retry = true;
				continue;
			}
			throw;	// rethrow here because we are done sending the request
		}
		catch(const std::exception& exc)
		{
			qCritical() << "Can't send request: " << exc.what();
			throw;	// same rethrow
		}
	} while(Retry);

	Poco::Net::HTTPResponse response;
	std::istream& received_stream = session.receiveResponse(response);
	return FormResponse(response, received_stream);
}

void HTTPClient::AddCredentials(Poco::Net::HTTPRequest& request)
{
    if (!m_token.empty())
    {
        request.setCredentials(m_auth_scheme, m_token);
    }
}
