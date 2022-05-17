#pragma once

#include <random>

#include "Net/Message.h"

Net::Response FormErrorResponse(
	Poco::Net::HTTPServerResponse::HTTPStatus status,
	std::string reason=std::string{});

Net::Response FormErrorResponse(
	Poco::Net::HTTPServerResponse::HTTPStatus status,
	const char* reason);

std::string HashingPassword(const std::string& password, const std::string& salt);

std::string CreateSalt();
