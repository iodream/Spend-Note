#include <iostream>
#include <sstream>
#include <QJsonObject>
#include <QString>

#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Message.h>

#include "Net/Message.h"
#include "Net/Constants.h"
#include "Net/Error.h"
#include "HTTPClient.h"

void HTTPClient::set_token(const std::string& str_token)
{
    m_token = str_token;
}

void HTTPClient::FormRequest(Poco::Net::HTTPRequest &request,
                             Poco::Net::HTTPClientSession &session,
                             const Net::Request &net_request)
{
    request.setContentType(net_request.content_type);
    if (net_request.content_type == Net::CONTENT_TYPE_APPLICATION_JSON)
    {
        QByteArray byte_array = net_request.json_playload.toJson();
        request.setContentLength(byte_array.size());
        std::ostream& o = session.sendRequest(request);
        o << net_request.json_playload.toJson().constData();
    }
    else if (net_request.content_type == Net::CONTENT_TYPE_PLAIN_TEXT)
        ;
    else if (net_request.content_type == Net::CONTENT_TYPE_EMPTY)
        ;
    else
    {
        throw ("Unsupported content type");
    }
}

Net::Response HTTPClient::FormResponse(const Poco::Net::HTTPResponse& response,
                                          std::istream &received_stream)
{
    Net::Response net_response;
    net_response.content_type = response.getContentType();
    net_response.status = response.getStatus();
    net_response.reason = response.getReason();
    std::stringstream ss;
    Poco::StreamCopier::copyStream(received_stream, ss);
    if (net_response.content_type == Net::CONTENT_TYPE_APPLICATION_JSON)
    {
        QByteArray br = QString::fromStdString(ss.str()).toUtf8();
        QJsonDocument json_doc = QJsonDocument::fromJson(br);
        net_response.json_playload = json_doc;
    }
    else if (net_response.content_type == Net::CONTENT_TYPE_PLAIN_TEXT)
        ;
    else if (net_response.content_type == Net::CONTENT_TYPE_EMPTY)
        ;
    else
    {
        throw ("Unsupported content type");
    }
    return net_response;
}

Net::Response HTTPClient::SendRequest(const Net::Request& net_request)
{
    Poco::URI uri(net_request.uri);
    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    std::string path(uri.getPathAndQuery());
    Poco::Net::HTTPRequest request(net_request.method, path, Poco::Net::HTTPMessage::HTTP_1_1);
    FormRequest(request, session, net_request);
    Poco::Net::HTTPResponse response;
    std::istream &received_stream = session.receiveResponse(response);
    return FormResponse(response, received_stream);
}
