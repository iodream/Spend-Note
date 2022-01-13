#pragma once

#include "Net/Message.h"

Net::Response FormJSONResponse(
	QJsonDocument&& json_doc,
	Poco::Net::HTTPServerResponse::HTTPStatus status=
	Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
