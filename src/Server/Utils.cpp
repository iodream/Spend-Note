#include "Utils.h"
#include "Logger/ScopedLogger.h"

Net::Response FormErrorResponse(
	Poco::Net::HTTPServerResponse::HTTPStatus status,
	std::string reason)
{
	SCOPED_LOGGER;
	Net::Response response;
	response.content_type = Net::CONTENT_TYPE_PLAIN_TEXT;
	if (reason.size())
		response.reason = reason;
	response.status = status;
	return response;
}


Net::Response FormErrorResponse(
	Poco::Net::HTTPServerResponse::HTTPStatus status,
	const char* reason)
{
	SCOPED_LOGGER;
	return FormErrorResponse(status, std::string(reason));
}
