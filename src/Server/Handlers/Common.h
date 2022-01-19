#pragma once

#include "Net/Message.h"

const std::string DB_CONN_STRING =
				"user=test_user host=127.0.0.1 "
				"password=test_pass dbname=SpendAndNote";

Net::Response FormJSONResponse(
	QJsonDocument&& json_doc,
	Poco::Net::HTTPServerResponse::HTTPStatus status=
	Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);
