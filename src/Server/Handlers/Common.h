#pragma once

#include "Net/Message.h"

const std::string DB_CONN_USER = "user=test_user";
const std::string DB_CONN_HOST = "host=127.0.0.1";
const std::string DB_CONN_PASS = "password=test_pass";
const std::string DB_CONN_DBNAME = "dbname=SpendAndNote";

Net::Response FormJSONResponse(
	QJsonDocument&& json_doc,
	Poco::Net::HTTPServerResponse::HTTPStatus status=
	Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_OK);


