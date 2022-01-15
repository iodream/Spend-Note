#pragma once

#include <memory>

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"

#include "Handlers/ICommandHandler.h"

class HTTPRequestHandler: public Poco::Net::HTTPRequestHandler
{
public:
    HTTPRequestHandler(ICommandHandler* handler) : m_handler{handler} {}
private:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
    QJsonDocument ReadJSON(std::istream& is);
    QJsonDocument AddTokenBody(const QJsonDocument& json_doc, const std::string& token_body);
    void CheckAuthorization(Poco::Net::HTTPServerRequest& request, std::string& token_body);
    /* token_body is Decoded JWT token body */
    void SendJSON(
        const QJsonDocument& json_doc,
        Poco::Net::HTTPServerResponse& response);
    void SendErrorResponse(
        Poco::Net::HTTPServerResponse::HTTPStatus status,
        Poco::Net::HTTPServerResponse& response);
private:
    std::unique_ptr<ICommandHandler> m_handler;
};
