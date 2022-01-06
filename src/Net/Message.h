#pragma once

#include <string>

#include "Poco/Net/HTTPServerResponse.h"

#include <QJsonDocument>

#include "Constants.h"

namespace Net {

struct Message
{
	ContentType content_type;
    QJsonDocument json_playload;
};


struct Request : public Message
{
	HTTPMethod method;
	AuthSchemeType auth_scheme;
    std::string auth_info;
	QJsonDocument JWT_token_body;
};

struct Response : public Message
{
    Poco::Net::HTTPResponse::HTTPStatus status;
    std::string reason;
};

}
