#pragma once

#include "Net/Message.h"

Net::Response FormErrorResponse(
	Poco::Net::HTTPServerResponse::HTTPStatus status,
	std::string reason=std::string{});

Net::Response FormErrorResponse(
	Poco::Net::HTTPServerResponse::HTTPStatus status,
	const char* reason);
