#include "Utils.h"


Net::Response FormErrorResponse(
	Poco::Net::HTTPServerResponse::HTTPStatus status,
	std::string reason)
{
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
	return FormErrorResponse(status, std::string(reason));
}
