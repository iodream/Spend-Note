#pragma once

#include "Net/Message.h"

extern const char* EMPTY_C_STRING;
extern const std::string EMPTY_STD_STRING;

Net::Response FormJSONResponse(
	QJsonDocument&& json_doc,
	Poco::Net::HTTPServerResponse::HTTPStatus status=
	Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
