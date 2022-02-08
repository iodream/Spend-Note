#include "MethodNotAllowedHandler.h"

#include "Server/Error.h"
#include "Server/Utils.h"

MethodNotAllowedHandler::MethodNotAllowedHandler()
{

}

Net::Response MethodNotAllowedHandler::Handle(Net::Request& request)
{
	Q_UNUSED(request);
	return FormErrorResponse(NetError::Status::HTTP_METHOD_NOT_ALLOWED);
}
