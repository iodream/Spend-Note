#pragma once

#include "Net/Message.h"

extern const char* EMPTY_C_STRING;
extern const std::string EMPTY_STD_STRING;

Net::Response FormJSONResponse(
	QJsonDocument&& json_doc,
	Poco::Net::HTTPServerResponse::HTTPStatus status=
	Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);

Net::Response FormJSONResponse(
	QJsonObject&& json,
	Poco::Net::HTTPServerResponse::HTTPStatus status=
	Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);

Net::Response FormJSONResponse(
	QJsonArray&& array,
	Poco::Net::HTTPServerResponse::HTTPStatus status=
	Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);

Net::Response FormEmptyResponse(
	Poco::Net::HTTPServerResponse::HTTPStatus status=
	Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_NO_CONTENT);

