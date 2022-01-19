#pragma once

#include <string>

#include "Poco/Net/HTTPServerResponse.h"

#include <QJsonDocument>

#include "Constants.h"
#include "Server/libdal/Types.h"

namespace Net {

struct Message
{
	ContentType content_type;
	QJsonDocument json_payload;
};

struct Request : public Message
{
	std::string uri;
	HTTPMethod method;
	AuthSchemeType auth_scheme;
	std::string auth_info;
	QJsonDocument jwt_token_body;
	IdType uid;
};

struct Response : public Message
{
	Poco::Net::HTTPResponse::HTTPStatus status;
	std::string reason;
};

}
